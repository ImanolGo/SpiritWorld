import socket
import struct
import sys

import time
from time import time as tt
import numpy as np
import os.path

from openframeworks import *
from protopixel import Content

import socket
UDP_IP = "192.168.1.100"
UDP_PORT = 2390

content = Content('Virtual controller')
content.add_parameter("FPS_LIMIT", min=0, max=60, value=30)

content.add_parameter("Controller1", value=False)
content.add_parameter("audio_react1", value=False)
content.add_parameter("IP_1", value="192.168.133.20")

content.add_parameter("Controller2", value=False)
content.add_parameter("audio_react2", value=False)
content.add_parameter("IP_2", value="192.168.133.21")

content.add_parameter("Controller3", value=False)
content.add_parameter("audio_react3", value=False)
content.add_parameter("IP_3", value="192.168.133.22")

content.add_parameter("Controller4", value=False)
content.add_parameter("audio_react4", value=False)
content.add_parameter("IP_4", value="192.168.133.23")


@content.parameter_changed('Output_name')
def output_name_changed(newval):
    #global FILEPATH
    #FILEPATH = "../../../"+newval+".txt"
    #print "New path:", newval
    pass

def setup():
    global controller, update_time, timmer, qframe, qtimmer, is_started,FPS
    print "SETUP------------------------"
    FPS = 30
    controller = None
    update_time = 1.0/FPS
    timmer = tt()
    qframe = 0
    qtimmer = tt()
    is_started = True
    #pt = ofToDataPath(".")
    #print pt,"-----------------ooooooooooo"
    

def update():
    global update_time, timmer, qframe, qtimmer, controller,FPS

    if controller != None and controller.outlets[0] != None:
        i = 0
        for q in range(4):
            msg = ""
            numlights = len(controller.outlets[i]) / 3
            if numlights < 200:
                msg = ''.join( chr(v) for v in controller.outlets[i])
                msg = msg + ''.join( [chr(0)] * ((200-numlights)*3))
            else:
                msg = ''.join( chr(v) for v in controller.outlets[i][0:600])
            i = i+1
            numlights = len(controller.outlets[i]) / 3
            if numlights < 200:
                msg = msg + ''.join( chr(v) for v in controller.outlets[i])
                msg = msg + ''.join( [chr(0)] * ((200-numlights)*3))
            else:
                msg = msg + ''.join( chr(v) for v in controller.outlets[i][0:600])
            i = i+1
            #print content['IP_'+str(i+1)]
            #print content['Controller'+str(i+1)]
            #msg = ''.join( [chr(255)] * ((400)*3))
            if content['Controller'+str(q+1)]:
                try:
                    print len(msg), content['IP_'+str(q+1)]
                    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # UDP
                    sock.sendto(msg, (content['IP_'+str(q+1)], UDP_PORT))
                except:
                    print "socket error unknown at device: "+str(q+1)

    #----------
    #FPS check
    #if qframe >= FPS-1:
    #    qframe = 0
    #    print tt() - qtimmer
    #    qtimmer = tt()
    #    print "------------------"
    #else:
    #    qframe = qframe + 1;
    #--------

    #--------
    #FPS limiter:
    actual = tt()
    elapsed = actual-timmer
    #30 fps --> 1/30
    diff = update_time- elapsed
    if diff > 0:
        time.sleep(diff)
    timmer = tt()
    FPS = content['FPS_LIMIT']
    update_time = 1.0/FPS
    #--------

def draw():
    pass

def exit():
    global controller
    print "EXIT------------------------"
    controller.running = False
    controller = None

def on_enable():
    global controller, is_started
    if not is_started:
        return
    print "ENABLE------------------------"
    controller = FakeTCPController()
    controller.listen() # obre el port
    #controller.announce() # fa un anounce

def on_disable():
    global controller
    print "DISABLE------------------------"
    controller.running = False
    controller = None

class FakeTCPController(object):
    def __init__(self):
        self.name = "Wifi"
        self.mac = "00:00:00:00:00:01"
        self.t = content.Thread(target=self._process)
        self.t.daemon = True
        self.running = False
        self.outlets = [np.zeros(0)]*8

    def announce(self):
        s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        message_version = 2
        firmware_version = 1
        hardware_version = 2
        mac_addr_1, mac_addr_2, mac_addr_3, mac_addr_4, mac_addr_5, mac_addr_6 = (0, 0, 0, 0, 0, 0)
        actual_ip_1, actual_ip_2, actual_ip_3, actual_ip_4 = (127, 0, 0, 1)
        properties = 0
        actual_gateway_1, actual_gateway_2, actual_gateway_3, actual_gateway_4 = (192, 168, 133, 1)
        actual_mask_1, actual_mask_2, actual_mask_3, actual_mask_4 = (255, 255, 255, 0)
        device_name = "WIFI"
        static_ip_1, static_ip_2, static_ip_3, static_ip_4 = (192, 168, 133, 222)
        static_gateway_1, static_gateway_2, static_gateway_3, static_gateway_4 = (192, 168, 133, 1)
        static_mask_1, static_mask_2, static_mask_3, static_mask_4 = (255, 255, 255, 0)
        message = struct.pack('<HHB6B4BB4B4B16s4B4B4B',
                              message_version,
                              firmware_version,
                              hardware_version,
                              mac_addr_1, mac_addr_2, mac_addr_3, mac_addr_4, mac_addr_5, mac_addr_6,
                              actual_ip_1, actual_ip_2, actual_ip_3, actual_ip_4,
                              properties,
                              actual_gateway_1, actual_gateway_2, actual_gateway_3, actual_gateway_4,
                              actual_mask_1, actual_mask_2, actual_mask_3, actual_mask_4,
                              device_name,
                              static_ip_1, static_ip_2, static_ip_3, static_ip_4,
                              static_gateway_1, static_gateway_2, static_gateway_3, static_gateway_4,
                              static_mask_1, static_mask_2, static_mask_3, static_mask_4,
                              )
        s.sendto(message, ('localhost', 5006))

    def listen(self):
        self.running = True
        self.t.start()

    def stop(self):
        self.running = False

    def _process(self):
        s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
        s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        s.bind(('localhost',5015))
        s.listen(1)
        s.settimeout(0.3)
        #self.timmer = tt()
        i = 0
        while self.running:
            try:
                i = (1 + i) % 10
                if i == 0:
                    self.announce()
                (ss, _) = s.accept()
                ss.settimeout(1)
                print "New Connection"
                while self.running:
                    header = ss.recv(23)
                    if not header:
                        break
                    assert header[:5] == "PROTO"
                    ss.send('ok')
                    LED_count = struct.unpack('>8H',header[7:7+8*2])
                    for i in range(8):
                        lcount = LED_count[i]
                        if lcount == 0:
                            continue
                        outletdata = ss.recv(lcount*3)
                        self.outlets[i] = np.fromstring(outletdata,dtype=np.uint8)
            except socket.timeout:
                pass
            except socket.error:
                pass
        s.close()

    def __del__(self):
        self.running = False
