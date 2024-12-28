from PIL import Image, ImageDraw, ImageFont

# Настройки
font_size = 16  # Размер шрифта
chars_per_row = 16  # Количество символов в строке
grid_size = font_size + 2  # Размер ячейки (с отступами)
output_size = (chars_per_row * grid_size, 6 * grid_size)  # Размер итогового изображения
font_path = "/usr/share/fonts/truetype/dejavu/DejaVuSerifCondensed-Bold.ttf"  # Путь к шрифту

# Создание изображения
image = Image.new("1", output_size, color=1)  # Монохромное изображение (1 бит на пиксель)
draw = ImageDraw.Draw(image)
font = ImageFont.truetype(font_path, font_size)

# Рисование символов
for i in range(32, 128):  # ASCII от 32 до 127
    x = ((i - 32) % chars_per_row) * grid_size
    y = ((i - 32) // chars_per_row) * grid_size
    draw.text((x + 1, y + 1), chr(i), font=font, fill=0)

# Сохранение в BMP
image.save("font_grid.bmp")
print("Шрифт сохранен в font_grid.bmp")

