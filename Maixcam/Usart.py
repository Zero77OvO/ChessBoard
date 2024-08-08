from maix import time
from maix.network import wifi
from maix import app, uart,pinmap




class python_usart:
  
    qipan_flag=0
    qizi_flag=0  

    def __init__(self, Pin_1, Pin_2, Rx, Tx, bitrate,device):

        pinmap.set_pin_function(Pin_1, Rx)
        pinmap.set_pin_function(Pin_2, Tx) 

        
        self.device = device
        self.serial = uart.UART(self.device, bitrate)

        
        self.USART_REC_LEN = 200
        self.USART_RX_BUF = [0] * 100
        self.USART_RX_STA = 0
        self.USART_NewData = None
        self.RxState = 0

        
        # self.serial.write("hello 1\r\n".encode())
        # self.serial.write_str("hello 2\r\n") 
        
              
   

        # self.publish_oceancat(self.Send_topic,Send_message)
        
                     
    def usart_receive(self):
        

        data = self.serial.read()
        if data:
            # print("Received, type: {}, len: {}, data: {}".format(type(data), len(data), data))
            for byte in data:
                # print(hex(byte))
                if self.RxState == 0 and byte== 0x2c:
                    self.USART_RX_BUF[self.USART_RX_STA]=byte
                    self.RxState = 1			
                    
                elif self.RxState == 1 and byte== 0x12:
                    self.USART_RX_STA+=1
                    self.USART_RX_BUF[self.USART_RX_STA]=byte
                    self.RxState = 2; 
                    # print(hex(byte))

                elif self.RxState ==2:
                    self.USART_RX_STA+=1
                    self.USART_RX_BUF[self.USART_RX_STA]=byte
                    if self.USART_RX_BUF[self.USART_RX_STA-1]== 0x5b: 
                        
                        self.qipan_flag= self.USART_RX_BUF[self.USART_RX_STA-3]
                        self.qizi_flag = self.USART_RX_BUF[self.USART_RX_STA-2]
                        
                        

                        
                        self.RxState=3; 
                        time.sleep_ms(10) 
                    
                elif self.RxState==3:
                    self.USART_RX_STA=0
                    self.USART_RX_BUF = [0] * 100
                    self.RxState=0
                    



###############USART##################
###############USART##################
Pin_1="A18"
Pin_2 ="A19"
Rx="UART1_RX" 
Tx="UART1_TX"
device="/dev/ttyS1"
bitrate=115200

qipan_open_flag=python_usart.qipan_flag
qizi_open_flag=python_usart.qizi_flag

Usart1=python_usart(Pin_1, Pin_2, Rx, Tx, bitrate,device)
###############USART##################
###############USART##################