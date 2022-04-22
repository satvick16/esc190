lDistance :: Eq a => [a] -> [a] -> Int
lDistance [] t = length t -- If s is empty, the distance is the number of characters in t
lDistance s [] = length s -- If t is empty, the distance is the number of characters in s
lDistance (a : s') (b : t') =
  if a == b
    then lDistance s' t' -- If the first characters are the same, they can be ignored
    else
      1
        + minimum -- Otherwise try all three possible actions and select the best one
          [ lDistance (a : s') t', -- Character is inserted (b inserted)
            lDistance s' (b : t'), -- Character is deleted  (a deleted)
            lDistance s' t' -- Character is replaced (a replaced with b)
          ]


int levenshtein(const char *s, int ls, const char *t, int lt)
{
        int a, b, c;
 
        /* if either string is empty, difference is inserting all chars 
         * from the other
         */
        if (!ls) return lt;
        if (!lt) return ls;
 
        /* if last letters are the same, the difference is whatever is
         * required to edit the rest of the strings
         */
        if (s[ls - 1] == t[lt - 1])
                return levenshtein(s, ls - 1, t, lt - 1);
 
        /* else try:
         *      changing last letter of s to that of t; or
         *      remove last letter of s; or
         *      remove last letter of t,
         * any of which is 1 edit plus editing the rest of the strings
         */
        a = levenshtein(s, ls - 1, t, lt - 1);
        b = levenshtein(s, ls,     t, lt - 1);
        c = levenshtein(s, ls - 1, t, lt    );
 
        if (a > b) a = b;
        if (a > c) a = c;
 
        return a + 1;
}
