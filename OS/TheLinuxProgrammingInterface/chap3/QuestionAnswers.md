3.1 
`magic2` 是一组生日日期，用来防止意外情况下（使用错误的系统调用号而调用了reboot、内存 corruption）调用了 reboot；
只有正确地给到这一组魔术后，才认定调用 reboot 是使用者的原始意图。
