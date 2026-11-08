from dictionary.base_dictionary import BaseDictionary
from dictionary.word_frequency import WordFrequency


# Class representing a node in the Trie
class TrieNode:
    def __init__(self):
        self.children = {}
        self.frequency = 0
        self.is_last = False


class TrieDictionary(BaseDictionary):
    def __init__(self):
        self.root = TrieNode()

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
        node = self.root
        for char in word:
            if char in node.children:
                node = node.children[char]
            else:
                return 0
        return node.frequency if node.is_last else 0

    def add_word_frequency(self, word_frequency: WordFrequency) -> bool:
        """
        Add a word and its frequency to the dictionary.
        @param word_frequency: (word, frequency) to be added
        @return: True whether succeeded, False when word is already in the dictionary
        """
        node = self.root
        for char in word_frequency.word:
            if char not in node.children:
                node.children[char] = TrieNode()
            node = node.children[char]

        if node.is_last:
            return False  # Word already exists
        node.is_last = True
        node.frequency = word_frequency.frequency
        return True

    def delete_word(self, word: str) -> bool:
        """
        Delete a word from the dictionary.
        @param word: word to be deleted
        @return: whether succeeded, e.g., return False when word not found
        """
        nodes = []
        node = self.root
        for char in word:
            if char in node.children:
                nodes.append((node, char))
                node = node.children[char]
            else:
                return False

        if not node.is_last:
            return False

        node.is_last = False
        node.frequency = 0

        if not node.children:
            for parent, char in reversed(nodes):
                del parent.children[char]
                if parent.is_last or parent.children:
                    break

        return True

    def autocomplete(self, prefix_word: str) -> [WordFrequency]:
        node = self.root
        for char in prefix_word:
            if char in node.children:
                node = node.children[char]
            else:
                return []

        def dfs(current_node, current_result, current_word):
            if current_node.is_last:
                current_result.append(WordFrequency(current_word, current_node.frequency))

            for child_char, child_node in current_node.children.items():
                dfs(child_node, current_result, current_word + child_char)

        result = []
        dfs(node, result, prefix_word)

        result.sort(key=lambda wf: wf.frequency, reverse=True)
        return result[:3]