
from dictionary.base_dictionary import BaseDictionary
from dictionary.word_frequency import WordFrequency

class ListNode:
    """
    Define a node in the linked list
    """

    def __init__(self, word_frequency: WordFrequency):
        self.word_frequency = word_frequency
        self.next = None


class LinkedListDictionary(BaseDictionary):
    def __init__(self):
        self.head = None

    def build_dictionary(self, words_frequencies: [WordFrequency]):
        """
        Construct the data structure to store nodes.
        @param words_frequencies: list of (word, frequency) to be stored
        """
        for word_frequency in words_frequencies:
            self.add_word_frequency(word_frequency)

    def search(self, word: str) -> int:
        """
        Search for a word.
        @param word: the word to be searched
        @return: frequency > 0 if found and 0 if NOT found
        """
        current = self.head
        while current:
            if current.word_frequency.word == word:
                return current.word_frequency.frequency
            current = current.next
        return 0

    def add_word_frequency(self, word_frequency: WordFrequency) -> bool:
        """
        Add a word and its frequency to the dictionary.
        @param word_frequency: (word, frequency) to be added
        @return: True whether succeeded, False when word is already in the dictionary
        """
        if self.search(word_frequency.word) > 0:
            return False  # Word already exists
        new_node = ListNode(word_frequency)
        new_node.next = self.head
        self.head = new_node
        return True

    def delete_word(self, word: str) -> bool:
        """
        Delete a word from the dictionary.
        @param word: word to be deleted
        @return: whether succeeded, e.g. return False when word not found
        """
        current = self.head
        if current and current.word_frequency.word == word:
            self.head = current.next
            return True

        prev = None
        while current:
            if current.word_frequency.word == word:
                prev.next = current.next
                return True
            prev = current
            current = current.next
        return False

    def autocomplete(self, prefix_word: str) -> [WordFrequency]:
        """
        Return a list of 3 most-frequent words in the dictionary that have 'prefix_word' as a prefix.
        @param prefix_word: word to be autocompleted
        @return: a list (could be empty) of (at most) 3 most-frequent words with prefix 'prefix_word'
        """
        word_frequencies = []
        current = self.head
        while current:
            if current.word_frequency.word.startswith(prefix_word):
                word_frequencies.append(current.word_frequency)
            current = current.next

        # Sort word frequencies by frequency in descending order and return the top 3
        word_frequencies.sort(key=lambda wf: wf.frequency, reverse=True)
        return word_frequencies[:3]
