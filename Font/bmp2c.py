from PIL import Image

def convert_bmp_to_linear_image(bmp_path, img_width, img_height, char_width, char_height, output_c_path, header_path):
    # Открываем BMP файл и конвертируем его в монохромное изображение
    image = Image.open(bmp_path)
    width, height = image.size

    if width != img_width or height != img_height:
        raise ValueError(f"Размеры изображения ({width}x{height}) не совпадают с указанными ({img_width}x{img_height}).")

    pixels = image.load()

    # Проверяем корректность параметров символов
    if img_width % char_width != 0 or img_height % char_height != 0:
        raise ValueError("Ширина и высота символов должны быть кратны ширине и высоте изображения.")

    chars_per_row = img_width // char_width
    total_chars = (img_width // char_width) * (img_height // char_height)
    linear_width = chars_per_row * char_width

    # Генерация .C файла
    with open(output_c_path, "w") as f:
        f.write(f"// Изображение, сгенерированное из {bmp_path}\n")
        f.write("#include <stdint.h>\n\n")
        f.write(f"const uint16_t image_linear_width = {linear_width};\n")
        f.write(f"const uint8_t char_width = {char_width};\n")
        f.write(f"const uint8_t char_height = {char_height};\n")
        f.write(f"const uint16_t total_chars = {total_chars};\n")
        f.write("const uint8_t image_data[] = {\n")

        for y in range(img_height):
            for x in range(img_width):
                if x % 8 == 0:
                    byte = 0
                if pixels[x, y] == 0:  # Черный пиксель
                    byte |= (1 << (7 - (x % 8)))
                if x % 8 == 7 or x == img_width - 1:
                    f.write(f"0x{byte:02X}, ")
            f.write("\n")

        f.write("};\n")

    # Генерация заголовочного файла
    with open(header_path, "w") as f:
        f.write("#ifndef IMAGE_DATA_H\n")
        f.write("#define IMAGE_DATA_H\n\n")
        f.write("#include <stdint.h>\n\n")
        f.write("extern const uint16_t image_linear_width;\n")
        f.write("extern const uint8_t char_width;\n")
        f.write("extern const uint8_t char_height;\n")
        f.write("extern const uint16_t total_chars;\n")
        f.write("extern const uint8_t image_data[];\n\n")
        f.write("#endif // IMAGE_DATA_H\n")

    print(f"Файл .C сохранён: {output_c_path}")
    print(f"Файл заголовка сохранён: {header_path}")

# Пример вызова функции
bmp_path = "Font/font_grid_with_cyrillic.bmp"  # Замените на ваш путь
img_width = 7744  # Укажите ширину изображения
img_height = 22  # Укажите высоту изображения
char_width = 22  # Укажите ширину символа
char_height = 22  # Укажите высоту символа
output_c_path = "font_data_dirt.c"
header_path = "font_data_dirt.h"

convert_bmp_to_linear_image (bmp_path, img_width, img_height, char_width, char_height, output_c_path, header_path)