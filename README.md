# strsub
simple find and replace on strings written in C

done using bare minimum built-in functions and data types. no arrays, string functions, etc.
just `int`, `int*`, `char`, and `char*`.

No idea if it is at all optimal. done more as an exercise and to brush up on my C programming.

If the pattern and replacement have the same length, then the original string can be modified in place.
Additionally, if the pattern and replacement are only a single character long, then we only need to find a single character.

If they aren't the same length, then I first go through and find how many matches there are so I can calculate the size
that will be needed for the final result.
That is also used to allocate space for the indices of each match, which are then found and stored in a second pass.
Finally, the non-matching parts of the string are moved over and at each of the indices where a match was found, the replacement is added.

