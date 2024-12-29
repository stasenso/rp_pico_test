from PIL import Image
import sys

def convert_bmp_to_font(bmp_path, img_width, img_height, char_width, char_height, output_c_path, header_path):
    # Открываем BMP файл и конвертируем его в монохромное изображение
    image = Image.open(bmp_path).convert("1")
    width, height = image.size

    if width != img_width or height != img_height:
        raise ValueError(f"Размеры изображения ({width}x{height}) не совпадают с указанными ({img_width}x{img_height}).")

    pixels = image.load()

    # Проверяем корректность параметров символов
    if img_width % char_width != 0 or img_height % char_height != 0:
        raise ValueError("Ширина и высота символов должны быть кратны ширине и высоте изображения.")

    chars_per_row = img_width // char_width
    chars_per_col = img_height // char_height
    total_chars = chars_per_row * chars_per_col

    # Генерация .C файла
    with open(output_c_path, "w") as f:
        f.write(f"// Шрифт, сгенерированный из {bmp_path}\n")
        f.write("#include <stdint.h>\n\n")
        f.write(f"const uint8_t font_width = {char_width};\n")
        f.write(f"const uint8_t font_height = {char_height};\n")
        f.write(f"const uint16_t font_char_count = {total_chars};\n")
        f.write("const uint8_t font_data[] = {\n")

        for char_y in range(chars_per_col):
            for char_x in range(chars_per_row):
                f.write(f"    // Символ ({char_x}, {char_y})\n")
                for y in range(char_height):
                    byte = 0
                    for x in range(char_width):
                        pixel_x = char_x * char_width + x
                        pixel_y = char_y * char_height + y
                        if pixels[pixel_x, pixel_y] == 0:  # Черный пиксель
                            byte |= (1 << (7 - (x % 8)))
                        if (x + 1) % 8 == 0 or x == char_width - 1:
                            f.write(f"0x{byte:02X}, ")
                            byte = 0
                    f.write("\n")
        f.write("};\n")

    # Генерация заголовочного файла
    with open(header_path, "w") as f:
        f.write("#ifndef FONT_DATA_H\n")
        f.write("#define FONT_DATA_H\n\n")
        f.write("#include <stdint.h>\n\n")
        f.write("extern const uint8_t font_width;\n")
        f.write("extern const uint8_t font_height;\n")
        f.write("extern const uint16_t font_char_count;\n")
        f.write("extern const uint8_t font_data[];\n\n")
        f.write("#endif // FONT_DATA_H\n")

    print(f"Файл .C сохранён: {output_c_path}")
    print(f"Файл заголовка сохранён: {header_path}")

# Пример вызова функции
bmp_path = "Font/font_grid_with_cyrillic.bmp"  # Замените на ваш путь
img_width = 704  # Укажите ширину изображения
img_height = 242  # Укажите высоту изображения
char_width = 22  # Укажите ширину символа
char_height = 22  # Укажите высоту символа
output_c_path = "font_data_dirt.c"
header_path = "font_data_dirt.h"

convert_bmp_to_font(bmp_path, img_width, img_height, char_width, char_height, output_c_path, header_path)