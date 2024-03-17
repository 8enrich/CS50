-- Keep a log of any SQL queries you execute as you solve the mystery.
.schema --I used this command to see the tables in the database

SELECT crime_scene_reports.description FROM crime_scene_reports
WHERE crime_scene_reports.year = 2020 AND crime_scene_reports.month = 7
AND crime_scene_reports.day = 28 AND crime_scene_reports.street = "Chamberlin Street"; -- I used this command to see the description of the exactly date and local of the crime_scene_reports

SELECT interviews.name, interviews.transcript FROM interviews WHERE interviews.year = 2020
AND interviews.month = 7 AND interviews.day = 28 AND interviews.transcript LIKE "%courthouse%"; -- I used this command to read all the transcripts that happened that day and contain courthouse

SELECT people.name FROM people WHERE people.license_plate IN(
SELECT courthouse_security_logs.license_plate FROM courthouse_security_logs
WHERE courthouse_security_logs.day = 28 AND courthouse_security_logs.month = 7 AND courthouse_security_logs.year = 2020
AND courthouse_security_logs.hour = 10 AND courthouse_security_logs.minute > 15 AND courthouse_security_logs.minute <= 25 AND courthouse_security_logs.activity = "exit"); -- I used this command to have an idea of the suspects

SELECT people.name FROM people JOIN bank_accounts ON person_id = people.id
WHERE account_number IN (SELECT atm_transactions.account_number FROM atm_transactions
WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street" AND transaction_type = "withdraw"); -- I used this command to have a list of suspects

SELECT name FROM people WHERE phone_number
IN(SELECT caller FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60); -- I used this command to have another list of suspects

SELECT name FROM people WHERE phone_number
IN(SELECT receiver FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60); -- I used this command to have another list of suspects that help the thief

SELECT id, hour, minute FROM flights WHERE year = 2020 AND month = 7 AND day = 29
AND origin_airport_id IN(SELECT id FROM airports WHERE city = "Fiftyville") ORDER BY hour; -- I used this command to see the id of the earlist flight that origin is Fiftyville

SELECT name, seat FROM people JOIN passengers ON passengers.passport_number = people.passport_number
WHERE flight_id = 36; -- I used this command to see who is in the earlist flight that origin is Fiftyville
