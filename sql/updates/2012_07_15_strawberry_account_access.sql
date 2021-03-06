-- command table
UPDATE command 
SET help = 'Syntax: .account set gmlevel [$account] #level [#realmid]\r\n\r\nSet the security level for targeted player (can''t be used at self) or for account $name to a level of #level on the realm #realmID.\r\n\r\n#level may range from 0 to 3.\r\n\r\n#reamID may be -1 for all realms.'
WHERE name = 'account set gmlevel';

INSERT INTO strawberry_string VALUES 
(11001, 'You have not chosen -1 or the current realmID that you are on.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);