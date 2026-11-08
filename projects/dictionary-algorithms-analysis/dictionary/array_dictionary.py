from dictionary.word_frequency import WordFrequency
from dictionary.base_dictionary import BaseDictionary


class ArrayDictionary(BaseDictionary):
    def __init__(self):
        self.words_frequencies = []

    def build_dictionary(self, words_frequencies: [WordFrequency]):
        # You can sort the list based on the 'word' attribute of WordFrequency objects
        self.words_frequencies = sorted(words_frequencies, key=lambda wf: wf.word)

    def search(self, word: str) -> int:
        for wf in self.words_frequencies:
            if wf.word == word:
                return wf.frequency
        return 0

    def add_word_frequency(self, word_frequency: WordFrequency) -> bool:
        for wf in self.words_frequencies:
            if wf.word == word_frequency.word:
                return False  # Word already exists
        self.words_frequencies.append(word_frequency)
        self.words_frequencies.sort(key=lambda wf: wf.word)  # Sort the list after addition
        return True

    def delete_word(self, word: str) -> bool:
        for wf in self.words_frequencies:
            if wf.word == word:
                self.words_frequencies.remove(wf)
                return True
        return False

    def autocomplete(self, prefix_word: str) -> [WordFrequency]:
        result = [wf for wf in self.words_frequencies if wf.word.startswith(prefix_word)]
        result.sort(key=lambda wf: wf.frequency, reverse=True)
        return result[:3]
