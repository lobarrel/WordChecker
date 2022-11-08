# WordChecker

This repository contains the code related to the 2022 Algorithms and Data Structures project (Politecnico di Milano).
The goal of the project was to implement the theoretical concepts learned during the course regarding algorithm complexity, data structures and efficiency. Concurrent programming was not allowed, as well as the usage of advanced libraries.

In the repo you can also find some input examples (and the expected output) to test the code.

# Assignment

At its core, the program checks the correspondance of letters between two words of the same length. Each word is a sequence of alphabetical characters (a-z, A-Z), digits (0-9), and special symbols (-, _).
Example: djHD1af9fj7g__l-ssOP (valid), jio?nbYF@091ns (not valid)

The program reads a sequence of instructions from the stardard input. 
In particular, the program reads:
- The length of the words ("k")
- A sequence (of arbitrary length, with no duplicates) of words (of length k) which represents the vocabulary


##Match structure

Then, the program reads a sequence of matches. The command to start a new match is "+nuova_partita" (new_match).
Inside each match the program reads:
- A secret word (the word to guess, we will call it "R")
- The maximum number of words to guess the secret word ("n")
- A sequence of words (of length k) to compare with the secret word (we will call each of this words "P")
The program can also read the command "+stampa_filtrate" which is explained later.

For each word P which has to be compared to the secret word R, the program prints on the standard output a sequence of k characters with the following criteria:
- "+" if P[i] = R[i] (the character at index "i" is in the correct position)
- "/" if P[i] is not present in R
- "|" if P[i] is present in R but in a different position. If R contains n instances of P[i] the program will first check if there are any in the correct positions, then it will check if there are any in a different position and if P contains more than n instances of that character, those in excess will be marked as "/".

Example 1:

R = abcabcabcabcabc

P = bbaabccbccbcabc

    /+|+++|++/+++++

Example 2:

R = djPDi939-s__e-s

P = gioSON-we2_w234

    /|////|/|/+//|/
    
If the program reads a word P which doesn't appear in the vocabulary, it prints "not_exists".

If the program reads a word P which is equal to R, it prints "ok" and the match ends.

After reading n words P, if none of these was equal to R, it prints "ko" and the match ends.


##Insert new words

During a match or between two matches the program can read the commands "+inserisci_inizio" (insert_begin) and "+inserisci_fine" (insert_end), with a list of words in between that are added to the vocabulary.


##Filtered words

Each comparison between P and R generates new constraints. From the comparison in the Example 1 (above) we learn that:
- "b" is in positions 2,5,8,11,14
- There are only 5 "b" (the sixth "b" produces "/" in output)
- "c" is in positions 6,9,12,15 and it's not in positions 7,10
- There are only 5 "c"
- "a" is in positions 4,13 and it's not in position 3

During a match, we call filtered words the words in the vocabulary that comply with all the constraints learned in all the previous comparisons of that match. When the program reads the command "+stampa_filtrate" (print_filtered) it prints the filtered words in alphabetical order (specified by the ASCII standard). Furthermore, after each comparison the program prints the number of filtered words, except if the result of the comparison is "not_exists".

