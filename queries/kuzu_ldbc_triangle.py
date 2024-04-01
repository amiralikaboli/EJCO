import shutil
import sys
import time

import kuzu

if __name__ == '__main__':
    SF = sys.argv[1]

    try:
        db = kuzu.Database('./db')
        conn = kuzu.Connection(db)

        with open(f"../data/LDBC/{SF}/schema.cypher", "r") as schema_file:
            for line in schema_file.readlines():
                conn.execute(line)
        with open(f"../data/LDBC/{SF}/copy.cypher", "r") as copy_file:
            for line in copy_file.readlines():
                conn.execute(line)

        iters = 10
        tm = time.time()
        for _ in range(iters):
            results = conn.execute(
                "MATCH (c:Comment)-[:replyOf_Post]->(p:Post)-[:Post_hasTag]->(t:Tag), (c)-[:Comment_hasTag]->(t) "
                "RETURN c.id, p.id, t.id"
            )
        print(round((time.time() - tm) / iters * 1000), "ms")
        # while results.has_next():
        #     print(results.get_next())
    except:
        raise
    finally:
        shutil.rmtree('./db')
