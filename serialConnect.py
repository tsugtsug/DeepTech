import serial

# シリアルポートの設定（Raspberry Piのデフォルトのシリアルポート）
serial_port = '/dev/AMC0'  # USBケーブルを使用 pinを使うなら '/dev/serial0'
baud_rate = 9600            # Arduino側と一致させる
timeout = 1

# シリアル通信の設定
ser = serial.Serial(serial_port, baud_rate, timeout=timeout)

print("Waiting for messages from Arduino...")

try:
    while True:
        # シリアルポートから1行のメッセージを受信
        if ser.in_waiting > 0:
            message = ser.readline().decode('utf-8').strip()
            print("Received message: ", message)
except KeyboardInterrupt:
    print("Exiting...")
finally:
    ser.close()

