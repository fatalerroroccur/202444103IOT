import serial
from influxdb_client import InfluxDBClient
import time

serial_port='COM9'
baud_rate=9600
timeout=2

influxdb_url="http://localhost:8086"
influxdb_token="fqvV9bApRMGWlaVqVztoLI6JQderIQLfQdHByvmjHcdkIehnE1TbdFIId7WRvHJuzVYpVgStsEMIX3nPBJth3w=="
influxdb_org = "test"
influxdb_bucket="dust"

client = InfluxDBClient(url=influxdb_url, token=influxdb_token, org=influxdb_org)
write_api = client.write_api()

try:
    ser=serial.Serial(serial_port, baud_rate, timeout = timeout)
    print(f"connected to {serial_port} at {baud_rate}baud")
except:
    print("failed")
    exit()
    
try:
    while True:
        if ser.in_waiting > 0:
            line=ser.readline().decode('utf-8').strip()

            if "=" in line:
                key, value = line.split("=")
                try:
                    value = float(value)
                    data=f"sensor_data,device=arduino {key}={value}"
                    write_api.write(bucket=influxdb_bucket, record=data)
                    print(f"Data written to influxdb: {key}={value}")
                except ValueError:
                    print("invalid data")
        time.sleep(1)
except KeyboardInterrupt:
    print("프로그램 종료")
finally:
    ser.close()
