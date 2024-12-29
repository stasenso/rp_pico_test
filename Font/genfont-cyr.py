from PIL import Image, ImageDraw, ImageFont

# Настройки
font_size = 20  # Размер шрифта
chars_per_row = 32  # Количество символов в строке
grid_size = font_size + 2  # Размер ячейки (с отступами)
font_path = "/usr/share/fonts/truetype/dejavu/DejaVuSerifCondensed.ttf"  # Путь к шрифту

# Диапазоны символов
ascii_range = range(32, 128)  # ASCII символы
cyrillic_range = range(0x0400, 0x0500)  # Кириллица (U+0400 - U+04FF)

# Объединённый диапазон символов
all_chars = list(ascii_range) + list(cyrillic_range)

# Вычисление размеров изображения
rows = (len(all_chars) + chars_per_row - 1) // chars_per_row
output_size = (chars_per_row * grid_size, rows * grid_size)

# Создание изображения
image = Image.new("1", output_size, color=1)  # Монохромное изображение (1 бит на пиксель)
draw = ImageDraw.Draw(image)
font = ImageFont.truetype(font_path, font_size)

# Рисование символов
for idx, char_code in enumerate(all_chars):
    x = (idx % chars_per_row) * grid_size
    y = (idx // chars_per_row) * grid_size
    draw.text((x + 1, y + 1), chr(char_code), font=font, fill=0)

# Сохранение в BMP
image.save("font_grid_with_cyrillic.bmp")
print("Шрифт с кириллицей сохранён в font_grid_with_cyrillic.bmp")
