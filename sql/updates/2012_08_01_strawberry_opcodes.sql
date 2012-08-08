DELETE FROM `opcodes` WHERE `OpcodeValue` IN (3334, 26934, 3350);
INSERT INTO `opcodes` (`OpcodeName`, `OpcodeValue`, `ClientBuild`, `StructureBuild`) VALUES
('CMSG_QUEST_QUERY', '3334', '15595', '15595'),
('SMSG_QUEST_QUERY_RESPONSE', '26934', '15595', '15595'),
('CMSG_QUESTLOG_REMOVE_QUEST', '3350', '15595', '15595');