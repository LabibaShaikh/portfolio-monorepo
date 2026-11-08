map transforms each element into an array
line => = arrow function syntax. Think of => as "becomes" or "transforms into"
What .map() Does:
"Take each element in this array, transform it somehow, and give me back a new array with all the transformed elements"

YES! You just unlocked a major insight! 🔓Code is absolutely read inside-out and right-to-left when you have chained methods. Let me show you:

where.exe node

Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser

Line 5: const expected = Number(row.expected_qty);
English: "Create a constant called expected, set it to the expected_qty value from row, converted to a number"

row.expected_qty = gets the expected_qty property (probably a string like "100")
Number() = converts it to an actual number type
Why? Because CSV data comes in as strings, but you need numbers for math

Step 1: today - arrival
When you subtract two Date objects, JavaScript gives you the difference in milliseconds.
Example:
javascriptconst today = new Date("2026-01-06");    // January 6, 2026
const arrival = new Date("2026-01-01");  // January 1, 2026

today - arrival = 432000000  // milliseconds between these dates

The replacer function only returns the VALUE, not the key-value pair.BUT — JSON.stringify automatically keeps the key and pairs it with whatever value you return!

fullName: data.name
↑         ↑
|         └─ Get the VALUE from data.name ("Alice")
└─ Use it as the value for a NEW key called "fullName"

JSON.stringify(result, null, 2)
               ↑       ↑     ↑
               |       |     └─── 3rd param: How many spaces to indent
               |       └───────── 2nd param: Replacer function (filtering)
               └───────────────── 1st param: The object to convert

You can even use a string!
javascriptJSON.stringify(result, null, "🎉");
Output:
json{
🎉"processed": [
🎉🎉{
🎉🎉🎉"shipment_id": "001"
🎉🎉}
🎉],
🎉"summary": {
🎉🎉"Complete": 5
🎉}
}
😂 (Don't do this in production!)

Your app uses Express, and express.json() lets Express read JSON data sent to your app and turn it into a JavaScript object (req.body).

3️⃣ Status codes (know these cold)
Situation	Code
Created	201
OK	200
No content	204
Bad input	400
Not found	404
Duplicate	409

5️⃣ Express mental map (burn this in)
Request
→ JSON middleware
→ validation
→ business logic
→ response


That’s the whole framework.

POST
Curl commands
\curl -X POST http://localhost:3000/orders \
  -H "Content-Type: application/json" \
  -d '{
    "id": "O1001",
    "customer_email": "user@example.com",
    "items": [
      { "sku": "BK001", "qty": 2 },
      { "sku": "BK010", "qty": 1 }
    ]
  }'

READ

curl http://localhost:3000/orders/01001

UPDATE

curl -X PUT http://localhost:3000/orders/01001 \
-H "Content-type: application/json" \
-d '{"status" : "fulfilled"}'

