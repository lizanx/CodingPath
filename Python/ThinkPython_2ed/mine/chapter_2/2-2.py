import math

# 1
print("The volume of a ball with radius=5 is", 4 / 3 * (5**3) * math.pi)

# 2
print("Total price is", (24.95 * (1 - 0.4) + 3) * 60 + 0.75 * 59)

# 3
total_secs = 1600/(1000/(6*60+10)) + 4800/(1000/(4*60+30)) + 1600/(1000/(6*60+10))
if total_secs >= 8 * 60:
    breakfast_time = f"7:{int((total_secs - 8 * 60) // 60)}"
else:
    breakfast_time = f"6:{int(total_secs // 60)}"
print("lunch time is", breakfast_time)