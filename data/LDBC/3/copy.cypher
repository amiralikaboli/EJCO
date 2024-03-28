COPY Comment FROM "../data/LDBC/3/comment.csv" (HEADER=true, DELIM='|');
COPY Post FROM "../data/LDBC/3/post.csv" (HEADER=true, DELIM='|');
COPY Tag FROM "../data/LDBC/3/tag.csv" (HEADER=true, DELIM='|');
COPY Comment_hasTag FROM "../data/LDBC/3/comment_hastag_tag.csv" (HEADER=true, DELIM='|');
COPY replyOf_Post FROM "../data/LDBC/3/comment_replyof_post.csv" (HEADER=true, DELIM='|');
COPY Post_hasTag FROM "../data/LDBC/3/post_hastag_tag.csv" (HEADER=true, DELIM='|');
