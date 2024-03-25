import shutil
import time

import kuzu

if __name__ == '__main__':
    try:
        db = kuzu.Database('./db')
        conn = kuzu.Connection(db)

        with open("../data/LDBC/schema.cypher", "r") as schema_file:
            for line in schema_file.readlines():
                conn.execute(line)
        with open("../data/LDBC/copy.cypher", "r") as copy_file:
            for line in copy_file.readlines():
                conn.execute(line)

        tm = time.time()
        for _ in range(100):
            results = conn.execute(
                "MATCH (c:Comment)-[:replyOf_Post]->(p:Post)-[:Post_hasTag]->(t:Tag), (c)-[:Comment_hasTag]->(t) "
                "RETURN count(*)"
            )
        print("Time: ", time.time() - tm)
        while results.has_next():
            print(results.get_next())
    except:
        raise
    finally:
        shutil.rmtree('./db')
