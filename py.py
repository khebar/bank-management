import torch
print(torch.__version__)                # مثلاً باید 2.3.0+cu121 باشه
print(torch.version.cuda)               # باید چیزی مثل '12.1' بده
print(torch.cuda.is_available())        # باید True باشه
print(torch.cuda.get_device_name(0))    # باید RTX 4050 بده
