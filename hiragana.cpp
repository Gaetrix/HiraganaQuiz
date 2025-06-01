#include <iostream>
#include <string>
#include <unordered_map>

// Konversi hiragana satu karakter ke romaji
std::string kanaToRomaji(char32_t kana) {
    static std::unordered_map<char32_t, std::string> map = {
        {U'あ', "a"},   {U'い', "i"},   {U'う', "u"},   {U'え', "e"},   {U'お', "o"},
        {U'か', "ka"},  {U'き', "ki"},  {U'く', "ku"},  {U'け', "ke"},  {U'こ', "ko"},
        {U'さ', "sa"},  {U'し', "shi"}, {U'す', "su"},  {U'せ', "se"},  {U'そ', "so"},
        {U'た', "ta"},  {U'ち', "chi"}, {U'つ', "tsu"}, {U'て', "te"},  {U'と', "to"},
        {U'な', "na"},  {U'に', "ni"},  {U'ぬ', "nu"},  {U'ね', "ne"},  {U'の', "no"},
        {U'は', "ha"},  {U'ひ', "hi"},  {U'ふ', "fu"},  {U'へ', "he"},  {U'ほ', "ho"},
        {U'ま', "ma"},  {U'み', "mi"},  {U'む', "mu"},  {U'め', "me"},  {U'も', "mo"},
        {U'や', "ya"},                 {U'ゆ', "yu"},                 {U'よ', "yo"},
        {U'ら', "ra"},  {U'り', "ri"},  {U'る', "ru"},  {U'れ', "re"},  {U'ろ', "ro"},
        {U'わ', "wa"},  {U'を', "o"},   {U'ん', "n"},
        {U'が', "ga"},  {U'ぎ', "gi"},  {U'ぐ', "gu"},  {U'げ', "ge"},  {U'ご', "go"},
        {U'ざ', "za"},  {U'じ', "ji"},  {U'ず', "zu"},  {U'ぜ', "ze"},  {U'ぞ', "zo"},
        {U'だ', "da"},  {U'ぢ', "ji"},  {U'づ', "zu"},  {U'で', "de"},  {U'ど', "do"},
        {U'ば', "ba"},  {U'び', "bi"},  {U'ぶ', "bu"},  {U'べ', "be"},  {U'ぼ', "bo"},
        {U'ぱ', "pa"},  {U'ぴ', "pi"},  {U'ぷ', "pu"},  {U'ぺ', "pe"},  {U'ぽ', "po"}
    };

    if (map.find(kana) != map.end()) {
        return map[kana];
    } else {
        return "";  // karakter tidak dikenali
    }
}

// Deteksi partikel dan ubah jadi bentuk benar
std::string fixParticles(std::string romaji, std::string hiraganaWord) {
    if (hiraganaWord == "は") return "wa";
    if (hiraganaWord == "へ") return "e";
    if (hiraganaWord == "を") return "o";
    return romaji;
}

int main() {
    std::u32string input;
    std::string line;

    std::cout << "Masukkan teks hiragana (gunakan spasi antar kata): ";
    std::getline(std::cin, line);

    // Konversi string UTF-8 ke UTF-32 (butuh compiler C++20)
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
    input = converter.from_bytes(line);

    std::string wordRomaji;
    std::string fullRomaji;

    for (char32_t c : input) {
        if (c == U' ') {
            fullRomaji += fixParticles(wordRomaji, ""); // Tidak tahu kata aslinya di sini
            fullRomaji += " ";
            wordRomaji.clear();
        } else {
            wordRomaji += kanaToRomaji(c);
        }
    }

    if (!wordRomaji.empty()) {
        fullRomaji += fixParticles(wordRomaji, ""); // akhir kalimat
    }

    std::cout << "Hasil romaji: " << fullRomaji << std::endl;
    std::cout << "Terjemahan Inggris: [belum tersedia di versi C++]" << std::endl;

    return 0;
}
