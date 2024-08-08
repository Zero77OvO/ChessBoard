'''
    Please read README.md first
    @author neucrack & lxowalle
    @license MIT
'''


from maix import camera, display, image, time, app, touchscreen
from collections import deque
import cv2
import numpy as np
from Usart import Usart1,qipan_open_flag,qizi_open_flag
import math

iRGB = lambda r, g, b: image.Color.from_rgb(r, g, b)
# 80 fps or 60fps
cam = camera.Camera(320, 320, fps=80)
disp = display.Display()
ts = touchscreen.TouchScreen()

mode = 1

Color=1

radius = 10

x1=0
y1=0
x2=0
y2=0
x3=0
y3=0
x4=0
y4=0
x5=0
y5=0
x6=0
y6=0
x7=0
y7=0
x8=0
y8=0
x9=0
y9=0


coordinates = {}

thresholds_total = []


thresholds = [[0, 80, 40, 80, 10, 80]] # red
usr_thresholds = [0, 0, 0, 0, 0, 0]

threshold_red = [0, 80, 30, 100, -120, -60]

threshold_white1 = [60, 89, -15, 12, -30, -10]
threshold_white2 = [70, 90, -13, 7, -26, -6]
threshold_white3 = [63, 83, -12, 8, -25, -5]

threshold_black1 = [0, 18, -3, 17, -12, 8]  
threshold_black2 = [0, 25, -10, 13, -9, 11]
threshold_black3 = [0, 25, -3, 17, -14, 6]
    

current_index = -1


get_label = "Get"
size = image.string_size(get_label)
get_btn_pos = [260, 0, 8*2 + size.width(), 12 * 2 + size.height()]

# draw start button
start_label = "Start   "
size = image.string_size(start_label)
start_btn_pos = [0, 60, 8*2 + size[0], 12 * 2 + size[1]]
# start_btn_pos[0] = disp.width() - start_btn_pos[2]

# draw color button
color_label = "Color"
size = image.string_size(color_label)
color_btn_pos = [0, 120, 8*2 + size[0], 12 * 2 + size[1]]

# # draw change button
# plus_label = "Plus+"
# size = image.string_size(plus_label)
# plus_btn_pos = [0, 180, 8*2 + size[0], 12 * 2 + size[1]]

# draw minus button
minus_label = "EXIT"
size = image.string_size(minus_label)
minus_btn_pos = [0, 240, 8*2 + size[0], 12 * 2 + size[1]]




def draw_btns(img):
    img.draw_string(268, 12, get_label, image.COLOR_GREEN)
    # img.draw_rect(get_btn_pos[0], get_btn_pos[1], get_btn_pos[2], get_btn_pos[3],  image.COLOR_WHITE, 2)
    # img.draw_rect(70, 0, 220, 320,  image.COLOR_WHITE, 2)


    img.draw_string(8, 132, color_label, image.COLOR_GREEN)
    # img.draw_rect(color_btn_pos[0], color_btn_pos[1], color_btn_pos[2], color_btn_pos[3],  image.COLOR_WHITE, 2)

    # img.draw_string(8, 192, plus_label, image.COLOR_GREEN)
    # img.draw_rect(plus_btn_pos[0], plus_btn_pos[1], plus_btn_pos[2], plus_btn_pos[3],  image.COLOR_WHITE, 2)

    img.draw_string(8, 252, minus_label, image.COLOR_GREEN)
    # img.draw_rect(minus_btn_pos[0], minus_btn_pos[1], minus_btn_pos[2], minus_btn_pos[3],  image.COLOR_WHITE, 2)
    
    


def is_in_button(x, y, btn_pos):
    return btn_pos[0] < x < btn_pos[0] + btn_pos[2] and btn_pos[1] < y < btn_pos[1] + btn_pos[3]

def collect_threshold_LAB(img,x,y):
    ROI = (x - radius, y - radius, radius * 2, radius * 2)
    Statistics = img.get_statistics(roi = ROI)
    thresholds = (Statistics.l_mode()-20,Statistics.l_mode()+20,
                Statistics.a_mode()-20,Statistics.a_mode()+20,
                Statistics.b_mode()-20,Statistics.b_mode()+20)
    print(x,y)
    img.draw_rect(x - radius, y - radius, radius * 2, radius * 2, color =image.COLOR_GREEN, thickness = 2)
    print(thresholds)
    return thresholds





executedOnce = True

start_blob_press = False
blobs_mode = False

points = deque()


    
    
    


def key_clicked(btn_rects):
    global last_pressed
    x, y, pressed = ts.read()
    if pressed:
        for i, btn in enumerate(btn_rects):
            if is_in_button(x, y, btn):
                if not last_pressed:
                    last_pressed = True
                    return True, i, btn
    else:
        last_pressed = False
    return False, 0, []

def check_mode_switch(img : image.Image, disp_w, disp_h):
    global mode
    btns = [
        [0, 0, 100, 40],
    ]
    btn_rects_disp = [image.resize_map_pos(img.width(), img.height(), disp_w, disp_h, image.Fit.FIT_CONTAIN, btns[0][0], btns[0][1], btns[0][2], btns[0][3])]
    clicked, idx, rect = key_clicked(btn_rects_disp)
    if clicked:
        mode += 1
        if mode > 3:
            mode = 1
    img.draw_string(2, 10, f"mode {mode}", color=image.COLOR_GREEN, scale=1.5)
    img.draw_rect(btns[0][0], btns[0][1], btns[0][2], btns[0][3], image.COLOR_GREEN, 2)
    
# def menu():

    
#     while mode == 3:

# 阈值距离
THRESHOLD_DISTANCE = 12 

qipan = [0] * 9

def euclidean_distance(x1, y1, x2, y2):
    return ((x1 - x2) ** 2 + (y1 - y2) ** 2) ** 0.5



def compare_coordinates(x_black, y_black, coordinates):
    for key, (x, y) in coordinates.items():
        distance = euclidean_distance(x_black, y_black, x, y)
        if distance <= THRESHOLD_DISTANCE:
            # print(f"Black piece is close to point {key} with distance {distance}")
            return key  # 返回贴合的标志
    return None

def update_qipan(x_piece, y_piece, piece_type, coordinates):
    global qipan
    for key, (x, y) in coordinates.items():
        distance = euclidean_distance(x_piece, y_piece, x, y)
        if distance <= THRESHOLD_DISTANCE:
            # print(f"Piece of type {piece_type} is close to point {key} with distance {distance}")
            qipan[key - 1] = piece_type  # 更新棋盘数组，key - 1 是因为数组索引从0开始  

                  
def is_qipan_nonzero(qipan):
    return any(value != 0 for value in qipan)

black_chess_coordinates = []
white_chess_coordinates = []


black_chess1_x = black_chess1_y = None
black_chess2_x = black_chess2_y = None
black_chess3_x = black_chess3_y = None
black_chess4_x = black_chess4_y = None
black_chess5_x = black_chess5_y = None

white_chess1_x = white_chess1_y = None
white_chess2_x = white_chess2_y = None
white_chess3_x = white_chess3_y = None
white_chess4_x = white_chess4_y = None
white_chess5_x = white_chess5_y = None

def is_coordinate_near(existing_coords, new_coord, threshold=10):
    """
    检查新坐标是否与已有坐标相近。
    threshold: 距离阈值，当距离小于该值时，认为坐标相近。
    """
    for coord in existing_coords:
        distance = math.sqrt((coord[0] - new_coord[0]) ** 2 + (coord[1] - new_coord[1]) ** 2)
        if distance < threshold:
            return True
    return False
          
def find_qipan():
    #menu
    global x1,y1,x2,y2,x3,y3,x4,y4,x5,y5,x6,y6,x7,y7,x8,y8,x9,y9
    global qipan
     
    global threshold_red
    global threshold_white1 
    global threshold_white2
    global threshold_white3

    global threshold_black1 
    global threshold_black2
    global threshold_black3
    
    global Color
    global current_index
    global thresholds_total
    global coordinates
    
    usr_thresholds = [0, 0, 0, 0, 0, 0]
    pause_press = False
    start_press = False
    color_press = False
    plus_press = False
    minus_press = False
    #menu
    
    ##########qipan###########
    find_center_method = 1  # 1, 2
    area_threshold_qipan = 80
    pixels_threshold_qipan = 50
    thresholds_qipan = [[0, 80, 0, 80, 30, 80]]        # red
    # thresholds = [[0, 80, -120, -10, 0, 30]]        # green
    # thresholds = [[0, 80, 30, 100, -120, -60]]    # blue
    
    ############pan##########
    
    ############qizi##########
    area_threshold_qizi = 300
    pixels_threshold_qizi = 300

    thresholds_total.append(threshold_red)
    thresholds_total.append(threshold_black1)
    thresholds_total.append(threshold_black2)
    thresholds_total.append(threshold_black3)
    thresholds_total.append(threshold_white1)
    thresholds_total.append(threshold_white2)
    thresholds_total.append(threshold_white3)
    
    t1=0
    ############qizi##########
    
    while mode == 1:
        
        x, y, pressed = ts.read()
        current_time = time.time()
        
        img = cam.read()
        img.lens_corr(strength=1.7)
        
        # check_mode_switch(img, disp.width(), disp.height())
        # roi=[1,1,img.width()-1, img.height()-1]
        # 70, 0, 220, 320
        blobs = img.find_blobs(thresholds_total, roi=[70,1,220, img.height()-1], x_stride=2, y_stride=1, area_threshold=area_threshold_qizi, pixels_threshold=pixels_threshold_qizi)
        # img.draw_rect(70, 0, 220, 320,  image.COLOR_GREEN, 2)
        draw_btns(img)
        img.draw_string(8, 72, f"C{Color}", image.COLOR_GREEN)
        # img.draw_rect(start_btn_pos[0], start_btn_pos[1], start_btn_pos[2], start_btn_pos[3],  image.COLOR_GREEN, 2)
        
        # img.draw_string(8, 290, str(usr_thresholds), image.COLOR_RED)
        x, y = image.resize_map_pos_reverse(img.width(), img.height(), disp.width(), disp.height(), image.Fit.FIT_CONTAIN, x, y)
        if t1>30:
            Usart1.usart_receive()
            t1=0
        if pressed:
            img.draw_circle(x, y, 1, image.Color.from_rgb(255, 255, 255), 2)
            if is_in_button(x, y, get_btn_pos):
                pause_press = True
                start_press = False
                color_press = False
                plus_press  = False
                minus_press = False

            if is_in_button(x, y, start_btn_pos):
                start_press = True
                pause_press = False
                color_press = False
                plus_press  = False
                minus_press = False
                executedOnce = True
                
            if is_in_button(x, y, color_btn_pos):
                executedOnce = True
                color_press = True
                pause_press = False
                start_press = False
                plus_press  = False
                minus_press = False

            # if is_in_button(x, y, plus_btn_pos):
            #     executedOnce = True
            #     plus_press  = True
            #     color_press = False
            #     pause_press = False
            #     start_press = False
            #     minus_press = False

        
            if is_in_button(x, y, minus_btn_pos):
                    infoimg = image.Image(
                            disp.width(), disp.height(), image.Format.FMT_RGB888
                        )
                    infoimg.draw_string(
                        disp.width() // 2 - 80,
                        disp.height() // 2,
                        "EXITING...",
                        color=iRGB(255, 0, 0),
                        scale=2,
                    )
                    disp.show(infoimg)
                    break

            points.append((x, y, current_time))

        else:
            if pause_press:
                # print(1)
                threshold = collect_threshold_LAB(img,x,y)
                print(x,y)
                usr_thresholds = list(threshold)
                
                #white
                if Color==1:
                    threshold_white1 = usr_thresholds
                    img.draw_string(8, 290, str(threshold_white1), image.COLOR_GREEN)
                #black    
                elif Color==2:
                    threshold_black1 = usr_thresholds
                    img.draw_string(8, 290, str(threshold_black1), image.COLOR_GREEN)

            if start_press:
                
                if executedOnce:
                    executedOnce = False
                    Color+=1
                    if Color > 2 :
                        Color=1
                
                
            if color_press:
                # print(3)
                if executedOnce:
                    executedOnce = False
                    
                    thresholds_total = []
                    thresholds_total.append(threshold_red)
                    thresholds_total.append(threshold_black1)
                    thresholds_total.append(threshold_black2)
                    thresholds_total.append(threshold_black3)
                    thresholds_total.append(threshold_white1)
                    thresholds_total.append(threshold_white2)
                    thresholds_total.append(threshold_white3)
                    img.draw_string(8, 290, str(threshold_white1), image.COLOR_GREEN)

            # if plus_press:
            #     #print(4)
            #     if executedOnce:
            #         executedOnce = False
            #         usr_thresholds[current_index] += 1
            #         thresholds = tuple(usr_thresholds)

            # if minus_press:
            #     #print(5)
            #     if executedOnce:
            #         executedOnce = False
            #         usr_thresholds[current_index] -= 1
            #         thresholds = tuple(usr_thresholds)

        while points and current_time - points[0][2] > 1:
            points.popleft()

        # disp.show(img, fit=image.Fit.FIT_CONTAIN)
        # time.sleep_ms(10)
          
        
     
        
        
        
        ############qipan###############
        
        
        if qipan_open_flag==0:
        
            # img = cam.read()
            # img.lens_corr(strength=1.7)
            # menu(img)
            # check_mode_switch(img, disp.width(), disp.height())
            img_cv = image.image2cv(img, False, False)
            gray = cv2.cvtColor(img_cv, cv2.COLOR_RGB2GRAY)

            # 高斯模糊去噪声
            # blurred = cv2.GaussianBlur(gray, (5, 5), 0)

            # 边缘检测
            edged = cv2.Canny(gray, 50, 100)

            # 膨胀处理
            kernel = np.ones((5, 5), np.uint8)
            dilated = cv2.dilate(edged, kernel, iterations=1)

            # disp.show(image.cv2image(dilated, False, False))
            # 查找轮廓
            contours, _ = cv2.findContours(dilated, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
            if len(contours) > 0:
                # 筛选出最大的轮廓
                largest_contour = max(contours, key=cv2.contourArea)

                # 近似多边形
                epsilon = 0.02 * cv2.arcLength(largest_contour, True)
                approx = cv2.approxPolyDP(largest_contour, epsilon, True)

                # 如果找到的是一个四边形
                if len(approx) == 4:
                    # print("rect found")
                    corners = approx.reshape((4, 2))

                    # 绘制顶点和轮廓
                    # for corner in corners:
                    #     cv2.circle(img_cv, tuple(corner), 4, (0, 255, 0), -1)

                    # 绘制四边路径性
                    # cv2.drawContours(img_cv, [approx], -1, (0, 255, 0), 1)

                    # 洪泛填充外部，如果棋盘外部的背景和棋盘内部的背景不同才需要这一步
                    img.flood_fill(corners[0][0] - 5, corners[0][1] - 5, 0.3, 0.3, image.COLOR_BLUE)
                    # img.flood_fill(corners[1][0] - 5, corners[1][1] + 5, 0.5, 0.05, image.COLOR_BLUE)
                    # img.flood_fill(corners[0][0] + 5, corners[0][1] + 5, 0.5, 0.05, image.COLOR_BLUE)
                    # img.flood_fill(corners[0][0] + 5, corners[0][1] - 5, 0.5, 0.05, image.COLOR_BLUE)

                    # 按顺序排列角点（左上、右上、右下、左下）
                    # rect = np.zeros((4, 2), dtype="float32")
                    # s = corners.sum(axis=1)
                    # rect[0] = corners[np.argmin(s)]
                    # rect[2] = corners[np.argmax(s)]
                    # diff = np.diff(corners, axis=1)
                    # rect[1] = corners[np.argmin(diff)]
                    # rect[3] = corners[np.argmax(diff)]

                    # (tl, tr, br, bl) = rect
                    # 上面出来的结果已经是 点从左上逆时针，所以跳过找顶点
                    tl = corners[0]
                    bl = corners[1]
                    br = corners[2]
                    tr = corners[3]

                        # print(f"Corner {i + 1}: {tuple(corner)}")
                        
                    # (corner1_x, corner1_y) = tuple(corners[0])
                    # (corner2_x, corner2_y) = tuple(corners[1])
                    # (corner3_x, corner3_y) = tuple(corners[2])
                    # (corner4_x, corner4_y) = tuple(corners[3]) 
                    # print("x1:{},y1:{},x2:{},y2:{},x3:{},y3:{},x4:{},y4:{}".format(corner1_x, corner1_y,corner2_x, corner2_y,corner3_x, corner3_y,corner4_x, corner4_y))
                    
                    # 计算3x3格子的交叉点
                    cross_points = []
                    for i in range(4):
                        for j in range(4):
                            # 线性插值计算交叉点
                            cross_x = int((tl[0] * (3 - i) + tr[0] * i) * (3 - j) / 9 +
                                        (bl[0] * (3 - i) + br[0] * i) * j / 9)
                            cross_y = int((tl[1] * (3 - i) + tr[1] * i) * (3 - j) / 9 +
                                        (bl[1] * (3 - i) + br[1] * i) * j / 9)
                            cross_points.append((cross_x, cross_y))
                            cv2.circle(img_cv, (cross_x, cross_y), 3, (0, 255, 0), -1)

                    centers = []
                    # 找格子中心点方法一：直接根据顶点计算
                    if find_center_method == 1:
                        for i in range(3):
                            for j in range(3):
                                center_x = int((cross_points[i * 4 + j][0] + cross_points[i * 4 + j + 1][0] + cross_points[(i + 1) * 4 + j][0] + cross_points[(i + 1) * 4 + j + 1][0]) / 4)
                                center_y = int((cross_points[i * 4 + j][1] + cross_points[i * 4 + j + 1][1] + cross_points[(i + 1) * 4 + j][1] + cross_points[(i + 1) * 4 + j + 1][1]) / 4)
                                centers.append((center_x, center_y))
                                cv2.circle(img_cv, (center_x, center_y), 2, (0, 255, 0), -1)
                    elif find_center_method == 2:
                        # 找格子中心点方法二： 找色块的方式来确定中心点
                        roi = [corners[:,0].min(), corners[:,1].min(), corners[:,0].max() - corners[:,0].min(), corners[:,1].max() - corners[:,1].min()]
                        img.draw_rect(roi[0], roi[1], roi[2], roi[3], image.COLOR_GREEN)
                        blobs = img.find_blobs(thresholds_qipan, roi=roi, x_stride=2, y_stride=1, area_threshold=area_threshold_qipan, pixels_threshold=pixels_threshold_qipan)
                        for b in blobs:
                            centers.append((b.cx(), b.cy()))
                            img.draw_circle(b.cx(), b.cy(), 2, image.COLOR_GREEN, -1)
                    else:
                        raise Exception("find_center_method value error")

                    # 对找到的中心点进行编号, y + x 最大就是右下角，最小就是左上角， y-x 最大就是左下角，y-x 最小就是右上角，其它几个点根据在旁边两个点中间判断
                    if len(centers) == 9:
                        centers = np.array(centers)
                        rect = np.zeros((9, 2), dtype="float32")
                        s = centers.sum(axis=1)
                        idx_0 = np.argmin(s)
                        idx_8 = np.argmax(s)
                        diff = np.diff(centers, axis=1)
                        idx_2 = np.argmin(diff)
                        idx_6 = np.argmax(diff)
                        rect[0] = centers[idx_0]
                        rect[2] = centers[idx_2]
                        rect[6] = centers[idx_6]
                        rect[8] = centers[idx_8]
                        #   其它点
                        calc_center = (rect[0] + rect[2] + rect[6] + rect[8]) / 4
                        mask = np.zeros(centers.shape[0], dtype=bool)
                        idxes = [1, 3, 4, 5, 7]
                        mask[idxes] = True
                        others = centers[mask]
                        idx_l = others[:,0].argmin()
                        idx_r = others[:,0].argmax()
                        idx_t = others[:,1].argmin()
                        idx_b = others[:,1].argmax()
                        found = np.array([idx_l, idx_r, idx_t, idx_b])
                        mask = np.isin(range(len(others)), found, invert=False)
                        idx_c = np.where(mask == False)[0]
                        if len(idx_c) == 1:
                            rect[1] = others[idx_t]
                            rect[3] = others[idx_l]
                            rect[4] = others[idx_c]
                            rect[5] = others[idx_r]
                            rect[7] = others[idx_b]
                            # 写编号
                            for i in range(9):
                                img.draw_string(rect[i][0], rect[i][1], f"{i + 1}", image.COLOR_GREEN, scale=2, thickness=-1)
                                x = int(rect[i][0] / 2)
                                y = int(rect[i][1] / 2)
                                coordinates[i + 1] = (x*2, y*2)
                                data3 = bytearray([0xF1, 0xF2, x, y, i+1, 0xF3])   
                                print("x:{}, y:{},location:{}".format(x*2, y*2,i+1)) 
                                Usart1.serial.write_str(data3)
                            #     if i == 0 : 
                            #         x1 = int(rect[i][0] / 2)
                            #         y1 = int(rect[i][1] / 2)
                            #         # print("x1:{},y1:{}".format(x1,y1))
                            #     if i == 2:  
                            #         x3 = int(rect[i][0] / 2)
                            #         y3 = int(rect[i][1] / 2)  
                            #         # print("x3:{},y3:{}".format(x3,y3))
                            # if x3 != x1 and x1!=0:
                            #     k = (y3 - y1) / (x3 - x1)
                            #     # 计算夹角（弧度）
                            #     theta_radians = math.atan(k)
                            #     # 将弧度转换为角度
                            #     theta_degrees = math.degrees(theta_radians)
                            # else:
                            #     # 处理垂直线的情况
                            #     k = float('inf')
                            #     theta_degrees = 90.0
                            # if(y1-y3)>10:
                            # data1=bytearray([0xA1, 0xB2, theta_degrees, 0xC3])
                            # print(theta_degrees-3.9)  
                            # Usart1.serial.write_str(data1)                                  
                            # if(y3-y1)>10:
                            #     data2=bytearray([0xA1, 0xB2, 2, 0xC3]) 
                            #     Usart1.serial.write_str(data2) 
                                

                        else:
                            # 大于 45度的情况
                            print("> 45 degree")
                          
        if qizi_open_flag ==0:   

            qipan = [0] * 9               
            for b in blobs:
                corners = b.mini_corners()
                
                # if b.code() == 1:
                #     for i in range(4):
                #         img.draw_line(corners[i][0], corners[i][1], corners[(i + 1) % 4][0], corners[(i + 1) % 4][1], image.COLOR_YELLOW, 2)
                
                ##WHITE       
                if b.code() == 32 or b.code() == 16 or b.code() == 8:
                    if 300 < b.area() < 3000:      # 过滤掉棋盘，认为area大于800时是棋盘，根据实际值调节
                        enclosing_circle = b.enclosing_circle()
                        img.draw_circle(enclosing_circle[0], enclosing_circle[1], enclosing_circle[2], image.COLOR_GREEN, 2)
                        
                        x_white = int(enclosing_circle[0])
                        y_white= int(enclosing_circle[1])
                        # 对比白棋与 九个格子的坐标
                        update_qipan(x_white, y_white, 1, coordinates)
                        
                        # new_coord_white = (x_white, y_white)
                        #  # 检查新坐标是否与已有坐标相近
                        # if not is_coordinate_near(white_chess_coordinates, new_coord_white):
                        #     # 存储白棋的坐标
                            # white_chess_coordinates.append(new_coord_white)
                            # if len(white_chess_coordinates) == 5:
                                
                            #     white_chess_coordinates.sort(key=lambda coord: coord[0])
                            #     (white_chess1_x, white_chess1_y) = white_chess_coordinates[0]
                            #     (white_chess2_x, white_chess2_y) = white_chess_coordinates[1]
                            #     (white_chess3_x, white_chess3_y) = white_chess_coordinates[2]
                            #     (white_chess4_x, white_chess4_y) = white_chess_coordinates[3]
                            #     (white_chess5_x, white_chess5_y) = white_chess_coordinates[4]
                            #     # data5 = bytearray([0x5B, 0x5C, white_chess1_x/2, white_chess1_y/2,white_chess2_x/2, white_chess2_y/2, white_chess3_x/2, white_chess3_y/2,white_chess4_x/2,white_chess4_y/2,white_chess5_x/2,white_chess5_y/2,0x5D]) 
                            #     print(f"black: {black_chess_coordinates}")
                            #     # Usart1.serial.write_str(data5)
                                
                            #     white_chess_coordinates.clear()
                        
                        
                ##BLACK   
                if b.code() == 1 or b.code() == 2 or b.code() == 4:
                    if 300 < b.area() < 3000:
                        enclosing_circle = b.enclosing_circle()
                        img.draw_circle(enclosing_circle[0], enclosing_circle[1], enclosing_circle[2], image.COLOR_RED, 2)
                        
                        x_black = int(enclosing_circle[0])
                        y_black = int(enclosing_circle[1])
                        
                        # 对比黑棋与 九个格子的坐标
                        update_qipan(x_black, y_black, 2, coordinates)                    
                        # new_coord_black = (x_black, y_black)
                        #  # 检查新坐标是否与已有坐标相近
                        # if not is_coordinate_near(black_chess_coordinates, new_coord_black):
                        #     # 存储黑棋的坐标
                        #     black_chess_coordinates.append(new_coord_black)
                        #     if len(black_chess_coordinates) == 5:
                        #         black_chess_coordinates.sort(key=lambda coord: coord[0])
                                
                        #         (black_chess1_x, black_chess1_y) = black_chess_coordinates[0]
                        #         (black_chess2_x, black_chess2_y) = black_chess_coordinates[1]
                        #         (black_chess3_x, black_chess3_y) = black_chess_coordinates[2]
                        #         (black_chess4_x, black_chess4_y) = black_chess_coordinates[3]
                        #         (black_chess5_x, black_chess5_y) = black_chess_coordinates[4]
                        #         # data6 = bytearray([0x6B, 0x6C, black_chess1_x/2,black_chess1_y/2,black_chess2_x/2, black_chess2_y/2, black_chess3_x/2, black_chess3_y/2,black_chess4_x/2,black_chess4_y/2,black_chess5_x/2,black_chess5_y/2,0x6D]) 
                        #         print(f"black: {black_chess_coordinates}")
                        #         # Usart1.serial.write_str(data6)
                                
                                
                        #         black_chess_coordinates.clear()
                            
                corners = b.corners() 
                                
                if is_qipan_nonzero(qipan):
                    # print("Qipan:", qipan)   
                    data4 = bytearray([0x4B, 0x4C, qipan[0],qipan[1],qipan[2], qipan[3], qipan[4], qipan[5],qipan[6],qipan[7],qipan[8],0x4D]) 
                    Usart1.serial.write_str(data4)
                                            
           
                        

        disp.show(img)



def main():
    while not app.need_exit():
        
        find_qipan()
        # find_qizi()
        # menu()
if __name__ == '__main__':
    try:
        main()
   
    except Exception:
        import traceback
        e = traceback.format_exc()
        print(e)
        img = image.Image(disp.width(), disp.height())
        img.draw_string(2, 2, e, image.COLOR_WHITE, font="hershey_complex_small", scale=0.6)
        disp.show(img)
        while not app.need_exit():
            time.sleep(0.2)
