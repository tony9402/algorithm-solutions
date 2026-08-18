-- Authored by: tony9402
-- Co-authored by: -
-- Link: https://leetcode.com/problems/article-views-i/submissions/1096674016
# Write your MySQL query statement below
SELECT DISTINCT author_id as id FROM Views WHERE author_id = viewer_id ORDER BY id;

/* Solution Description
*/
