from PIL import Image
import sys

# Открываем BMP файл
bmp_path = "/home/smikhai/Repo/rp_pico_test/Font/font_grid_with_cyrillic.bmp"  # Путь к вашему BMP файлу
output_c_path = "font_data.c"  # Выходной файл для подключения в проект
image = Image.open(bmp_path).convert("1")  # Монохромное изображение

# Получаем пиксели
pixels = image.load()
width, height = image.size

# Генерация C-кода
with open(output_c_path, "w") as f:
    f.write(f"// Шрифт, сгенерированный из {bmp_path}\n")
    f.write("#include <stdint.h>\n\n")
    f.write(f"const uint8_t font_width = {width};\n")
    f.write(f"const uint8_t font_height = {height};\n")
    f.write("const uint8_t font_data[] = {\n")

    for y in range(height):
        for x in range(0, width, 8):
            byte = 0
            for bit in range(8):
                if x + bit < width and pixels[x + bit, y] == 0:  # Черный пиксель
                    byte |= (1 << (7 - bit))
            f.write(f"0x{byte:02X}, ")
        f.write("\n")

    f.write("};\n")
print(f"Данные шрифта сохранены в {output_c_path}")
