# Chess

This code is simple and non finished version of chess.
I used here two-dimensional arrays to create border, board, to implement figure into the matrix.

At this moment code checks next errors:

1. // Error 0 - Same color figures attacks each other.
2. // Error 1 - Color
3. // Error 2 - Figure's name
4. // Error 3 - Coordinate Error
5. // Error 4 - Empty starting coordinate
6. //  Error 5 - starting figure
7. // Error 6 - Movement Rule
8. //  Error 7 - Check and Mate


At this moment I have somekind of error about checking the king. I don't know why but it works everytime. Sometimes figures can move legally but system says that this is illegal moves.

Tutorial:

White figures:
Pawn - WP;
Rock - WR;
Knight - WN;
Bishop - WB;
Queen - WQ;
King - WK.

Black figures:
Pawn - BP;
Rock - BR;
Knight - BN;
Bishop - BB;
Queen - BQ;
King - BK.

Use figure color and name as it is written. WP
Next text is starting coordinate a-h 1-8.  a1,a2,a3...h8.
Next text is ending coordinate.

Example: WP e2 e4
