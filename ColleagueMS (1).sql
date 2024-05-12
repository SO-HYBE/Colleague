CREATE DATABASE  IF NOT EXISTS `colleagues` /*!40100 DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci */ /*!80016 DEFAULT ENCRYPTION='N' */;
USE `colleagues`;
-- MySQL dump 10.13  Distrib 8.0.36, for Win64 (x86_64)
--
-- Host: 127.0.0.1    Database: colleagues
-- ------------------------------------------------------
-- Server version	8.0.36

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
-- Table structure for table `courses`
--

DROP TABLE IF EXISTS `courses`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `courses` (
  `course_id` int NOT NULL,
  `course_name` varchar(100) DEFAULT NULL,
  `credit_hours` int DEFAULT NULL,
  `num_students_enrolled` int DEFAULT NULL,
  `staff_id` int DEFAULT NULL,
  PRIMARY KEY (`course_id`),
  KEY `staff_id` (`staff_id`),
  CONSTRAINT `courses_ibfk_1` FOREIGN KEY (`staff_id`) REFERENCES `staff` (`staff_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `courses`
--

LOCK TABLES `courses` WRITE;
/*!40000 ALTER TABLE `courses` DISABLE KEYS */;
INSERT INTO `courses` VALUES (155,'Computer Architecture',3,40,1952),(256,'Computer Vision',5,15,1952),(257,'Distrbuted Systems',4,27,1956),(276,'Databases',3,50,1953),(313,'Programming Techniques',3,45,1966),(322,'Digital Electronics',4,62,1958),(333,'Humanities',2,35,1959),(352,'Microcontroller',3,35,1955),(355,'Math 1',3,30,1967),(444,'Operating Systems',3,60,1969),(666,'OOP',3,66,1966),(811,'Math 2 ',3,30,1965),(822,'Marketing',2,50,1970),(833,'Numerical Analysis',3,70,1954),(844,'Technical Writing',2,60,1968),(855,'Dicrete Math',3,70,1954),(866,'Signal Theory',3,58,1963),(877,'Software Engineering',3,35,1953),(888,'Communication technologies',4,40,1957),(899,'Production Engineering',3,30,1964),(962,'Control Systems',4,27,1962),(963,'Computer Networks',4,45,1961),(964,'Embedded Systems',3,25,1960);
/*!40000 ALTER TABLE `courses` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `grades`
--

DROP TABLE IF EXISTS `grades`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `grades` (
  `grade_id` int NOT NULL AUTO_INCREMENT,
  `course_id` int DEFAULT NULL,
  `student_id` int DEFAULT NULL,
  `mark` int DEFAULT NULL,
  `grade` varchar(2) DEFAULT NULL,
  PRIMARY KEY (`grade_id`),
  KEY `student_id` (`student_id`),
  KEY `course_id` (`course_id`),
  CONSTRAINT `grades_ibfk_1` FOREIGN KEY (`course_id`) REFERENCES `courses` (`course_id`),
  CONSTRAINT `grades_ibfk_2` FOREIGN KEY (`student_id`) REFERENCES `students` (`student_id`),
  CONSTRAINT `grades_ibfk_3` FOREIGN KEY (`student_id`) REFERENCES `students` (`student_id`),
  CONSTRAINT `grades_ibfk_4` FOREIGN KEY (`course_id`) REFERENCES `courses` (`course_id`)
) ENGINE=InnoDB AUTO_INCREMENT=831 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `grades`
--

LOCK TABLES `grades` WRITE;
/*!40000 ALTER TABLE `grades` DISABLE KEYS */;
INSERT INTO `grades` VALUES (1,355,12221,90,'A'),(2,355,12222,90,'A'),(3,355,12223,92,'A'),(4,355,12224,92,'A'),(5,355,12225,98,'A+'),(6,355,12226,93,'A'),(7,355,12227,86,'B'),(8,355,12228,89,'A-'),(9,355,12229,94,'A'),(10,355,12230,79,'C+'),(11,355,12231,64,'D+'),(12,355,12232,69,'C-'),(13,355,12233,78,'B-'),(14,355,12234,91,'A'),(15,444,12221,95,'A+'),(16,444,12222,90,'A'),(17,444,12223,75,'C'),(18,444,12224,78,'B-'),(19,444,12225,91,'A'),(20,444,12226,76,'C+'),(21,444,12240,93,'A'),(22,444,12241,86,'B+'),(23,444,12242,88,'A-'),(24,444,12231,62,'D'),(25,444,12232,65,'D+'),(26,444,12233,80,'B'),(27,666,12221,85,'B'),(28,666,12222,93,'A'),(29,666,12223,92,'A'),(30,666,12224,96,'A+'),(31,666,12225,80,'B'),(32,666,12226,78,'B-'),(33,666,12227,68,'C-'),(34,666,12228,72,'C'),(35,666,12229,79,'C+'),(36,666,12230,90,'A'),(37,666,12231,85,'B'),(38,666,12240,88,'A-'),(39,666,12241,92,'A'),(40,811,12221,86,'B+'),(41,811,12222,90,'A'),(42,811,12223,86,'B+'),(43,811,12224,88,'A-'),(44,811,12225,92,'A'),(45,811,12226,79,'C+'),(46,811,12227,93,'A'),(47,811,12228,75,'C'),(48,811,12229,78,'B-'),(49,811,12230,82,'B'),(50,811,12231,79,'C+'),(51,811,12232,90,'A'),(52,811,12233,85,'B'),(53,822,12221,88,'A-'),(54,822,12222,92,'A'),(55,822,12223,79,'C+'),(56,822,12224,90,'A'),(57,822,12225,85,'B'),(58,822,12226,88,'A-'),(59,822,12229,92,'A'),(60,822,12231,79,'C+'),(61,822,12232,90,'A'),(62,822,12236,85,'B'),(63,833,12221,88,'A-'),(64,833,12222,92,'A'),(65,833,12223,79,'C+'),(66,833,12224,90,'A'),(67,833,12225,85,'B'),(68,833,12226,88,'A-'),(69,833,12235,92,'A'),(70,833,12240,79,'C+'),(71,313,12221,90,'A'),(72,313,12222,85,'B'),(73,313,12223,88,'A-'),(74,313,12224,92,'A'),(75,313,12225,79,'C+'),(76,313,12226,90,'A'),(77,276,12221,85,'B'),(78,276,12222,88,'A-'),(79,276,12223,92,'A'),(80,276,12224,79,'C+'),(81,276,12225,90,'A'),(82,276,12226,85,'B'),(83,276,12240,88,'A-'),(84,276,12241,92,'A'),(85,276,12242,79,'C+'),(86,155,12230,49,'F'),(87,155,12231,80,'B'),(88,155,12232,89,'A-'),(89,155,12233,83,'B'),(90,155,12234,86,'B+'),(91,155,12235,94,'A'),(92,155,12236,70,'C'),(93,155,12237,60,'D'),(94,155,12238,92,'A'),(95,155,12239,79,'C+'),(96,155,12240,90,'A'),(97,155,12241,85,'B'),(98,256,12235,78,'B-'),(648,355,12221,90,'A'),(649,355,12222,90,'A'),(650,355,12223,92,'A'),(651,355,12224,92,'A'),(652,355,12225,98,'A+'),(653,355,12226,93,'A'),(654,355,12227,86,'B'),(655,355,12228,89,'A-'),(656,355,12229,94,'A'),(657,355,12230,79,'C+'),(658,355,12231,64,'D+'),(659,355,12232,69,'C-'),(660,355,12233,78,'B-'),(661,355,12234,91,'A'),(662,444,12221,95,'A+'),(663,444,12222,90,'A'),(664,444,12223,75,'C'),(665,444,12224,78,'B-'),(666,444,12225,91,'A'),(667,444,12226,76,'C+'),(668,444,12240,93,'A'),(669,444,12241,86,'B+'),(670,444,12242,88,'A-'),(671,444,12231,62,'D'),(672,444,12232,65,'D+'),(673,444,12233,80,'B'),(674,666,12221,85,'B'),(675,666,12222,93,'A'),(676,666,12223,92,'A'),(677,666,12224,96,'A+'),(678,666,12225,80,'B'),(679,666,12226,78,'B-'),(680,666,12227,68,'C-'),(681,666,12228,72,'C'),(682,666,12229,79,'C+'),(683,666,12230,90,'A'),(684,666,12231,85,'B'),(685,666,12240,88,'A-'),(686,666,12241,92,'A'),(687,811,12221,86,'B+'),(688,811,12222,90,'A'),(689,811,12223,86,'B+'),(690,811,12224,88,'A-'),(691,811,12225,92,'A'),(692,811,12226,79,'C+'),(693,811,12227,93,'A'),(694,811,12228,75,'C'),(695,811,12229,78,'B-'),(696,811,12230,82,'B'),(697,811,12231,79,'C+'),(698,811,12232,90,'A'),(699,811,12233,85,'B'),(700,822,12221,88,'A-'),(701,822,12222,92,'A'),(702,822,12223,79,'C+'),(703,822,12224,90,'A'),(704,822,12225,85,'B'),(705,822,12226,88,'A-'),(706,822,12229,92,'A'),(707,822,12231,79,'C+'),(708,822,12232,90,'A'),(709,822,12236,85,'B'),(710,833,12221,88,'A-'),(711,833,12222,92,'A'),(712,833,12223,79,'C+'),(713,833,12224,90,'A'),(714,833,12225,85,'B'),(715,833,12226,88,'A-'),(716,833,12235,92,'A'),(717,833,12240,79,'C+'),(718,313,12221,90,'A'),(719,313,12222,85,'B'),(720,313,12223,88,'A-'),(721,313,12224,92,'A'),(722,313,12225,79,'C+'),(723,313,12226,90,'A'),(724,276,12221,85,'B'),(725,276,12222,88,'A-'),(726,276,12223,92,'A'),(727,276,12224,79,'C+'),(728,276,12225,90,'A'),(729,276,12226,85,'B'),(730,276,12240,88,'A-'),(731,276,12241,92,'A'),(732,276,12242,79,'C+'),(733,155,12230,49,'F'),(734,155,12231,80,'B'),(735,155,12232,89,'A-'),(736,155,12233,83,'B'),(737,155,12234,86,'B+'),(738,155,12235,94,'A'),(739,155,12236,70,'C'),(740,155,12237,60,'D'),(741,155,12238,92,'A'),(742,155,12239,79,'C+'),(743,155,12240,90,'A'),(744,155,12241,85,'B'),(745,256,12235,78,'B-'),(746,256,12243,92,'A'),(747,256,12244,79,'C+'),(748,256,12245,91,'A'),(749,257,12246,83,'B'),(750,257,12247,64,'D+'),(751,257,12248,92,'A'),(752,257,12249,77,'C+'),(753,257,12250,77,'C+'),(754,257,12251,87,'B+'),(755,257,12252,89,'A-'),(756,257,12253,98,'A+'),(757,257,12254,76,'C+'),(758,257,12255,76,'C+'),(759,322,12248,85,'B'),(760,322,12249,89,'A-'),(761,322,12250,90,'A'),(762,322,12251,78,'C+'),(763,322,12252,67,'C-'),(764,322,12253,86,'B+'),(765,322,12254,67,'C-'),(766,322,12255,90,'A'),(767,352,12236,93,'A'),(768,352,12237,87,'B'),(769,352,12238,51,'F'),(770,352,12239,52,'F'),(771,352,12240,79,'C+'),(772,352,12241,90,'A'),(773,352,12242,89,'A-'),(774,352,12243,88,'A-'),(775,352,12244,82,'B'),(776,352,12245,78,'C+'),(777,352,12246,77,'C+'),(778,352,12247,85,'B'),(779,352,12248,87,'B+'),(780,352,12249,92,'A'),(781,352,12250,97,'C+'),(782,352,12251,98,'A+'),(783,352,12252,87,'B+'),(784,352,12253,88,'A-'),(785,844,12245,91,'A'),(786,844,12246,64,'D+'),(787,844,12247,91,'A'),(788,844,12248,85,'B'),(789,844,12249,68,'C-'),(790,844,12250,93,'A'),(791,844,12251,52,'F'),(792,844,12252,90,'A'),(793,844,12253,70,'C'),(794,844,12254,73,'C'),(795,844,12255,92,'A'),(796,855,12242,79,'C+'),(797,855,12243,90,'A'),(798,855,12245,85,'B'),(799,855,12246,88,'A-'),(800,855,12247,92,'A'),(801,855,12248,79,'C+'),(802,855,12249,90,'A'),(803,855,12250,85,'B'),(804,855,12251,88,'A-'),(805,855,12252,92,'A'),(806,866,12245,79,'C+'),(807,866,12246,90,'A'),(808,866,12247,85,'B'),(809,866,12248,78,'B-'),(810,866,12249,82,'B'),(811,866,12250,90,'A'),(812,866,12251,90,'A'),(813,866,12252,95,'A+'),(814,866,12253,89,'A-'),(815,866,12254,94,'A'),(816,866,12255,77,'C+'),(817,963,12243,69,'C-'),(818,963,12244,87,'B+'),(819,963,12245,88,'A-'),(820,963,12246,92,'A'),(821,963,12247,79,'C+'),(822,963,12248,90,'A'),(823,963,12249,85,'B'),(824,963,12250,88,'A-'),(825,963,12251,92,'A'),(826,963,12252,79,'C+'),(827,963,12253,90,'A'),(828,963,12254,85,'B'),(829,963,12255,88,'A-'),(830,963,12228,92,'A');
/*!40000 ALTER TABLE `grades` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `staff`
--

DROP TABLE IF EXISTS `staff`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `staff` (
  `staff_id` int NOT NULL,
  `professor_name` varchar(100) DEFAULT NULL,
  `phone_number` varchar(20) DEFAULT NULL,
  PRIMARY KEY (`staff_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `staff`
--

LOCK TABLES `staff` WRITE;
/*!40000 ALTER TABLE `staff` DISABLE KEYS */;
INSERT INTO `staff` VALUES (1952,'Dr. Ahmed','011256325'),(1953,'Prof. Mohamed','011263252'),(1954,'Dr. Abdalrahman','01125395'),(1955,'Dr. Ahmed Salah','01067678282'),(1956,'Prof.Wael Elemary','01282828282'),(1957,'Dr. Mostafa Zaki','01045459999'),(1958,'Dr. Muhammed Elkady','012 59598342'),(1959,'Dr.Safaa Hegazy','01099667744'),(1960,'Dr. Hadia Mahmoud','01172726161'),(1961,'Dr. Nermine Salah','01148629561'),(1962,'Dr.Marwa Moustafa','01532324545'),(1963,'Dr.Ahmed Abdelhalim','01181817643'),(1964,'Dr. Shahira Elwakeel','01096784560'),(1965,'Dr.Nadia Elgendy','01125676700'),(1966,'Dr.Hadeer Ahmed','01156660066'),(1967,'Dr.Omar Zaher','01101119012'),(1968,'Prof.Fathy Mahmoud','01237845609'),(1969,'Dr. Hesham Abdelhady','01090123562'),(1970,'Dr.Mahmoud Shadi','01241413784');
/*!40000 ALTER TABLE `staff` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `students`
--

DROP TABLE IF EXISTS `students`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `students` (
  `student_id` int NOT NULL,
  `name` varchar(100) DEFAULT NULL,
  `gpa` decimal(3,2) DEFAULT NULL,
  `level` int DEFAULT NULL,
  `courses_enrolled` int DEFAULT NULL,
  PRIMARY KEY (`student_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `students`
--

LOCK TABLES `students` WRITE;
/*!40000 ALTER TABLE `students` DISABLE KEYS */;
INSERT INTO `students` VALUES (12221,'Hadeer Abdelwahab',3.90,3,5),(12222,'Sohybe Ibrahim',3.90,2,5),(12223,'Muhammad Hussein',3.90,2,5),(12224,'Omar Khaled',3.90,2,5),(12225,'Hady Diaa',3.90,2,4),(12226,'Radwa Hesham',3.80,3,5),(12227,'Serine Aisser',3.50,4,5),(12228,'Donia Ramy',3.50,4,5),(12229,'Mai Muhammad',4.00,3,5),(12230,'Malak Mahmoud',4.00,1,6),(12231,'Shaden Khaled',3.80,2,7),(12232,'Marwan Abdelrahman',3.88,3,5),(12233,'Abdelrahman Helmy',2.49,1,4),(12234,'Muhammad Youssef',3.50,2,7),(12235,'Noha Ali',2.90,3,6),(12236,'Abdullatif Elsawaf',3.33,2,5),(12237,'Omar Moustafa',3.55,2,6),(12238,'Youssef Salah',2.98,3,5),(12239,'Tala Emam',3.22,1,5),(12240,'Radwan Mahmoud',3.00,3,6),(12241,'Alaa Ali',3.40,3,6),(12242,'Sarah  Abdelrahman',2.82,4,4),(12243,'Hana Abdelwahab',4.00,1,6),(12244,'Maria Michael',3.50,1,5),(12245,'Salma Samy',3.10,1,4),(12246,'Nourhan Mahmoud',2.40,2,6),(12247,'Abdallah Hany',3.62,2,6),(12248,'Solaf Zahran',2.76,2,5),(12249,'Hassan Mohamed',2.90,2,5),(12250,'Ahmed Abed',3.30,2,4),(12251,'Youssef Abotaleb',3.00,3,4),(12252,'Rawan Arafa',3.80,3,7),(12253,'Adel Zaky',3.00,3,5),(12254,'Moustafa Mahmoud',3.60,3,7),(12255,'Rana Mohsen',3.50,4,7);
/*!40000 ALTER TABLE `students` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping events for database 'colleagues'
--

--
-- Dumping routines for database 'colleagues'
--
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2024-05-06 15:46:06
