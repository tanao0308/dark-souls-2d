from PIL import Image, ImageDraw

# 创建透明背景画布
size = 256
img = Image.new('RGBA', (size, size), (0,0,0,0))
draw = ImageDraw.Draw(img)

# 画蓝色实心圆
radius = size // 2 - 10
draw.ellipse((size//2 - radius, size//2 - radius, size//2 + radius, size//2 + radius), fill=(0, 153, 255,150))

# 保存 PNG
img.save('blue_circle.png')
