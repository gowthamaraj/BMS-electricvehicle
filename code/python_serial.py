import serial



from influxdb import InfluxDBClient

client = InfluxDBClient(host='localhost', port=8086)


client.switch_database('network')

ser = serial.Serial('COM3',9600,timeout=1)

while(1):
     t1=int(ser.readline().decode('ascii'))

   
    soc1=int(ser.readline().decode('ascii'))
    soc2=int(ser.readline().decode('ascii'))
    soc3=int(ser.readline().decode('ascii'))
    soc= int((soc1+soc2+soc3)/3)
   

    
    json_body = [ { "measurement": "bms_ev", "tags": { "user": "data", }, "fields": { "temp": t1, "soc1": soc1,"soc2":soc2,"soc3":soc3,"soc":soc, } } ]
    
        
    client.write_points(json_body)