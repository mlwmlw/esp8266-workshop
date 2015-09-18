i2c.setup(0, 2, 1, i2c.SLOW)
lcd = dofile("lcd1602.lua")(0x20)
print("lcd init")
lcd.put(lcd.locate(0, 0), "Hello, ESP8266!")