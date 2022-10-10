# C++ Markdown Page Search Engine
## Program which parses Markdown pages into search terms and allows user to search for pages which contain these terms
- Uses state machine design to parse through markdown syntax to differentiate between normal text and links to other pages, so that the user can query both seperately
- Utilizes object oriented programming to generalize operations for "and", "or", and "diff" on sets of search query results.
- Leverages HashMap, Set and vector properties to allow for O(1) average runtime for look up for any given search query

