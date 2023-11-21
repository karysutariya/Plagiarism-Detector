#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

class RollingTechnique {
public:
    RollingTechnique(const std::string& text_data, int size)
        : text_data(text_data), size(size), base_for_hash(26), start_win(0), end_win(0), mod_for_hash(5807) {
        hash = CalculateHash();
    }

    int CalculateHash() {
        int value_of_hash = 0;
        for (int i = 0; i < size; ++i) {
            value_of_hash = (value_of_hash + (text_data[i] - 'a') * static_cast<int>(std::pow(base_for_hash, size - i - 1))) % mod_for_hash;
        }
        start_win = 0;
        end_win = size;
        return value_of_hash;
    }

    bool NextWindow() {
        if (text_data.size() - 1 >= end_win) {
            hash = (((hash - (text_data[start_win] - 'a') * static_cast<int>(std::pow(base_for_hash, size - 1))) * base_for_hash) + text_data[end_win] - 'a') % mod_for_hash;
            ++start_win;
            ++end_win;
            return true;
        } else {
            return false;
        }
    }

    int GetHash() const {
        return hash;
    }

private:
    std::string text_data;
    int size;
    int base_for_hash;
    int start_win;
    int end_win;
    int mod_for_hash;
    int hash;
};

class PlagiarismDetector {
public:
    PlagiarismDetector(const std::string& file_no_one, const std::string& file_no_two)
        : file_no_one(file_no_one), file_no_two(file_no_two), hash_storage({{"a", {}}, {"b", {}}}), n_gram(5) {
        std::string content_of_one = ReadContentFile(file_no_one);
        std::string content_of_two = ReadContentFile(file_no_two);
        CountHash(content_of_one, "a");
        CountHash(content_of_two, "b");
    }

    void CountHash(const std::string& content, const std::string& doc_type) {
        std::string text_data = CleanData(content);
        RollingTechnique rolling_technique(text_data, n_gram);
        for (size_t i = 0; i < content.size() - n_gram + 1; ++i) {
            hash_storage[doc_type].push_back(rolling_technique.GetHash());
            if (!rolling_technique.NextWindow()) {
                break;
            }
        }
    }

    int PlagiarismAnswer() {
        size_t hash_storage_one = hash_storage["a"].size();
        size_t hash_storage_two = hash_storage["b"].size();
        size_t sh = CountIntersection(hash_storage["a"], hash_storage["b"]);
        double p = (2.0 * sh) / (hash_storage_one + hash_storage_two) * 100;
        return (p >= 28.5) ? 1 : 0;
    }

    std::string RemoveBib(const std::string& data) {
        std::vector<std::string> lines = SplitLines(data);
        std::string fin;
        for (const auto& line : lines) {
            std::vector<std::string> words = SplitWords(line);
            int count1 = 0;
            int count = 0;
            for (const auto& word : words) {
                ++count1;
                if (std::isupper(word[0]) || std::any_of(word.begin(), word.end(), ::isdigit)) {
                    ++count;
                }
            }
            if (count < (count1 / 2)) {
                fin += line;
            }
        }
        return fin;
    }

    std::string RemoveRef(const std::string& data) {
        std::string data_without_bib = RemoveBib(data);
        std::vector<std::string> sentences = SplitSentences(data_without_bib);
        std::string fin;
        size_t count = sentences.size();
        size_t c = 1;
        for (const auto& sentence : sentences) {
            std::smatch test;
            if (!std::regex_search(sentence, test, std::regex("[\\(|\\[|\\{]\\s*(.*)\\s*[\\)|\\]|\\}]\\z"))) {
                if (count != c) {
                    fin += sentence + ". ";
                } else {
                    fin += sentence;
                }
            }
            ++c;
        }
        return fin;
    }

    std::string ReadContentFile(const std::string& filename) {
        std::ifstream file(filename);
        if (file.is_open()) {
            std::string contents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
            return RemoveRef(contents);
        } else {
            return "";
        }
    }

    std::string CleanData(const std::string& content) {
        std::string content1 = ToLowercase(content);
        const std::unordered_set<std::string> stop_words{
            "ourselves", "hers", "between", "yourself", "but", "again", "there", "about", "once", "during", "out", "very", "having", "with", "they", "own", "an", "be", "some", "for",
            "do", "its", "yours", "such", "into", "of", "most", "itself", "other", "off", "is", "s", "am", "or", "who", "as", "from", "him", "each", "the", "themselves", "until", "below",
            "are", "we", "these", "your", "his", "through", "don", "nor", "me", "were", "her", "more", "himself", "this", "down", "should", "our", "their", "while", "above", "both", "up",
            "to", "ours", "had", "she", "all", "no", "when", "at", "any", "before", "them", "same", "and", "been", "have", "in", "will", "on", "does", "yourselves", "then", "that", "because",
            "what", "over", "why", "so", "can", "did", "not", "now", "under", "he", "you", "herself", "has", "just", "where", "too", "only", "myself", "which", "those", "i", "after", "few", "whom",
            "t", "being", "if", "theirs", "my", "against", "a", "by", "doing", "it", "how", "further", "was", "here", "than"
        };
        const std::string special_chars = "!\"#$%&()*+/:;<=>@[\\]^`{|}~\t";
