import pykakasi
from deep_translator import GoogleTranslator

def hiragana_to_romaji_with_particles(text):
    kakasi = pykakasi.kakasi()
    kakasi.setMode("H", "a")
    kakasi.setMode("K", "a")
    kakasi.setMode("J", "a")
    kakasi.setMode("r", "Hepburn")
    kakasi.setMode("s", True)  # Split words
    kakasi.setMode("C", True)  # Add character type info

    converter = kakasi.getConverter()
    result = converter.convert(text)

    romaji_words = []
    for item in result:
        orig = item['orig']
        roma = item['hepburn']

        # Koreksi partikel
        if orig == "は":
            roma = "wa"
        elif orig == "へ":
            roma = "e"
        elif orig == "を":
            roma = "o"

        romaji_words.append(roma)

    return ' '.join(romaji_words)

def translate_to_english(text):
    try:
        translated = GoogleTranslator(source='ja', target='en').translate(text)
        return translated
    except Exception as e:
        return f"[Terjemahan gagal: {e}]"

if __name__ == "__main__":
    hiragana_input = input("Masukkan teks hiragana: ")
    romaji_output = hiragana_to_romaji_with_particles(hiragana_input)
    english_output = translate_to_english(hiragana_input)

    print("\nHasil Romaji :", romaji_output)
    print("English:", english_output)
