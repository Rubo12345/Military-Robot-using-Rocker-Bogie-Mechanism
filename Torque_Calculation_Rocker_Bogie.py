# Wheel torque Calculation
# Nw = Number of wheels
# GVW = Gross vehicle weight (GVW) , unit - kg
# Rw = Radius of each wheels, unit - m
# slope (a) = Max.gradient of slope, unit - degree
# Vmax = Max.linear velocity, unit - m/s
# Crr = Surface friction co-efficient (Crr of the sand is consider)
# Rolling Resistance (RR) = GVW x Crr
# Grade Resistance (GR) = GVW X Sin(a)
#Acceleration Force (FA) = (GVW X Vmax)/32.2 ft/s2 x 1s
# Total Tractive Force (TTE) = RR + GR + FA
# RF = Resistance Factor (RF)  (values ranges between 1.1 to 1.15)
# Wheel Torque (Tw) = TTE X RW X RF, unit - Kg-cm

import math
import numpy as np
def Torque_Calc(GVW, Rw, a, Vmax, Crr, RF):
    RR = GVW * Crr
    print("The angle of inclination in radians is:", math.sin(a))
    GR = GVW * math.sin(a)
    FA = (GVW * Vmax)/9.81* 1
    TTE = RR + GR + FA
    TF = TTE/6
    Tw = (TF * Rw * 100 * RF)
    print("The Rolling Resistance is:", RR,"kg")
    print("The Grade Resistance is:", GR,"Kg")
    print("The Acceleration Force is:", FA,"Kg")
    print("The Total Tractive Force is:", TTE,"Kg")
    return Tw
print("The torque in kg-cm is:",Torque_Calc(4.5,0.05,np.pi/4,0.15,0.17,1.1),"Kg-cm")


