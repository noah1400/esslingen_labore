-- MySQL dump 10.13  Distrib 8.0.33, for Win64 (x86_64)
--
-- Host: 127.0.0.1    Database: filerDB
-- ------------------------------------------------------
-- Server version	8.0.33

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `Tdirectory`
--
USE filerdb;
DROP TABLE IF EXISTS `Tdirectory`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `Tdirectory` (
  `directory_id` int NOT NULL AUTO_INCREMENT,
  `group_id` int NOT NULL,
  `user_id` int NOT NULL,
  `name` varchar(255) NOT NULL,
  `subdir_id` int NOT NULL,
  `created_at` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `updated_at` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`directory_id`),
  KEY `tdirectory_user_id_foreign_idx` (`user_id`),
  KEY `tdirectory_group_id_foreign_idx` (`group_id`),
  CONSTRAINT `tdirectory_group_id_foreign` FOREIGN KEY (`group_id`) REFERENCES `Tgroupmembers` (`group_id`),
  CONSTRAINT `tdirectory_user_id_foreign` FOREIGN KEY (`user_id`) REFERENCES `Tusers` (`user_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Tdirectory`
--

LOCK TABLES `Tdirectory` WRITE;
/*!40000 ALTER TABLE `Tdirectory` DISABLE KEYS */;
/*!40000 ALTER TABLE `Tdirectory` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Tfiles`
--

DROP TABLE IF EXISTS `Tfiles`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `Tfiles` (
  `file_id` int NOT NULL AUTO_INCREMENT,
  `directory_id` int NOT NULL,
  `file_size` int NOT NULL,
  `store_path` varchar(255) NOT NULL,
  PRIMARY KEY (`file_id`),
  KEY `tfiles_directory_id_foreign_idx` (`directory_id`),
  CONSTRAINT `tfiles_directory_id_foreign` FOREIGN KEY (`directory_id`) REFERENCES `Tdirectory` (`directory_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Tfiles`
--

LOCK TABLES `Tfiles` WRITE;
/*!40000 ALTER TABLE `Tfiles` DISABLE KEYS */;
/*!40000 ALTER TABLE `Tfiles` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Tgroupmembers`
--

DROP TABLE IF EXISTS `Tgroupmembers`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `Tgroupmembers` (
  `member_id` int NOT NULL AUTO_INCREMENT,
  `group_id` int NOT NULL,
  `permissions` enum('r','rw') NOT NULL DEFAULT 'r',
  `user_id` int NOT NULL,
  PRIMARY KEY (`member_id`),
  KEY `tgroupmembers_user_id_foreign_idx` (`user_id`),
  KEY `tgroupmembers_group_id_foreign_idx` (`group_id`),
  CONSTRAINT `tgroupmembers_group_id_foreign` FOREIGN KEY (`group_id`) REFERENCES `Tgroups` (`group_id`),
  CONSTRAINT `tgroupmembers_user_id_foreign` FOREIGN KEY (`user_id`) REFERENCES `Tusers` (`user_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Tgroupmembers`
--

LOCK TABLES `Tgroupmembers` WRITE;
/*!40000 ALTER TABLE `Tgroupmembers` DISABLE KEYS */;
/*!40000 ALTER TABLE `Tgroupmembers` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Tgroups`
--

DROP TABLE IF EXISTS `Tgroups`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `Tgroups` (
  `group_id` int NOT NULL AUTO_INCREMENT,
  `founder_id` int NOT NULL,
  `created_at` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `updated_at` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`group_id`),
  KEY `tgroups_founder_id_foreign_idx` (`founder_id`),
  CONSTRAINT `tgroups_founder_id_foreign` FOREIGN KEY (`founder_id`) REFERENCES `Tusers` (`user_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Tgroups`
--

LOCK TABLES `Tgroups` WRITE;
/*!40000 ALTER TABLE `Tgroups` DISABLE KEYS */;
/*!40000 ALTER TABLE `Tgroups` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Tusers`
--

DROP TABLE IF EXISTS `Tusers`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `Tusers` (
  `user_id` int NOT NULL AUTO_INCREMENT,
  `e_mail` varchar(255) NOT NULL,
  `password` varchar(255) NOT NULL,
  `role` enum('user','admin') NOT NULL DEFAULT 'user',
  `fName` varchar(255) NOT NULL,
  `lName` varchar(255) NOT NULL,
  `dob` date NOT NULL,
  PRIMARY KEY (`user_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Tusers`
--

LOCK TABLES `Tusers` WRITE;
/*!40000 ALTER TABLE `Tusers` DISABLE KEYS */;
/*!40000 ALTER TABLE `Tusers` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2023-05-17 12:36:53
