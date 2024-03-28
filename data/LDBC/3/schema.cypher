create node table Comment (id int64, creationDate INT64, locationIP STRING, browserUsed STRING, content STRING, length INT32, PRIMARY KEY (id));
create node table Post (id INT64, imageFile STRING, creationDate INT64, locationIP STRING, browserUsed STRING, language STRING, content STRING, length INT32, PRIMARY KEY (id));
create node table Tag (id INT64, name STRING, url STRING, PRIMARY KEY (id));
create rel table Comment_hasTag (FROM Comment TO Tag, MANY_MANY);
create rel table replyOf_Post (FROM Comment TO Post, MANY_ONE);
create rel table Post_hasTag (FROM Post TO Tag, MANY_MANY);
