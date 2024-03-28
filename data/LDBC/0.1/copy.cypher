COPY Comment FROM "../data/LDBC/0.1/Comment.csv" (HEADER=true, DELIM='|');
COPY Post FROM "../data/LDBC/0.1/Post.csv" (HEADER=true, DELIM='|');
COPY Tag FROM "../data/LDBC/0.1/Tag.csv" (HEADER=true, DELIM='|');
COPY Comment_hasTag FROM "../data/LDBC/0.1/Comment_hasTag_Tag.csv" (HEADER=true, DELIM='|');
COPY replyOf_Post FROM "../data/LDBC/0.1/Comment_replyOf_Post.csv" (HEADER=true, DELIM='|');
COPY Post_hasTag FROM "../data/LDBC/0.1/Post_hasTag_Tag.csv" (HEADER=true, DELIM='|');
