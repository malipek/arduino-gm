import boto3
import serial
ser = serial.Serial('/dev/ttyACM0')
ser.flushInput()
while True:
    ser_bytes = ser.readline()
    decoded_bytes = ser_bytes[0:len(ser_bytes)-2].decode("utf-8")
    client = boto3.client('lambda')
    response = client.invoke( FunctionName = "put-records", InvocationType = "RequestResponse", Payload = decoded_bytes)
    print(response['Payload'].read())
