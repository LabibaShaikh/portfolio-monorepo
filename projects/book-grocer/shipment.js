// csv input
const csvData = `
shipment_id,supplier,arrival_date,expected_qty,received_qty
S1001,Penguin,2026-01-02,10,10
S1002,HarperCollins,2026-01-03,12,9
S1003,Penguin,2026-01-01,8,0
S1004,Macmillan,2026-01-05,5,7
S1005,,2026-01-04,6,6
S1006,RandomHouse,invalid-date,4,4
S1002,HarperCollins,2026-01-03,12,9
`;


// Helper functions:

// 1.parseCSV

function parseCSV(csv){
    const lines = csv.trim().split("\n");
    const headers = lines[0].split(",");

    return lines.slice(1).map((line) => {
        const values = line.split(",");
        const row = {};

        headers.forEach((header, index)=> { // for each header as well as its position number do this
            //row[header] = values[index]?.trim();

// English: "In the row object, create a property with the header name.
// and set it to the corresponding value (if it exists), trimmed"
            row[header] = values[index]?.trim();

        });

        return row;
    });
}

// 2. Validation logic

    function validateRow(row){
        const errors = [];

        if(!row.shipment_id){
           errors.push("Missing shipment_id");
        }

        const date = new Date(row.arrival_date);
        if(isNaN(date.getTime())){
            errors.push("Invalid arrival_date");
        }

        const expected = Number(row.expected_qty);
        const received = Number(row.received_qty);

        if(!Number.isInteger(expected) || expected < 0){
            errors.push("Invalid expected_qty")
        }

         if(!Number.isInteger(received) || received < 0){
            errors.push("Invalid received_qty")
        }

        return errors;
    }


// 3. Derive shipment status

    function deriveStatus(expected, received){
        if (received === 0) return "Not received";
        if (received < expected) return "Partial";
        if (received === expected) return "Complete";

        return "Over-received";
    }

// 4.  Decide if something is an exception

    function isException(record, today){
        if(record.status === "Partial" || record.status === "Over-received"){
            return "Quantity Mismatch";
        }
        if(record.status === "Not received"){
            const arrival = new Date(record.arrival_date);
            const daysOld = (today - arrival) / (1000*60*60*24);

            if ( daysOld > 3){
                return "Overdue";
            }
        }

        return null;  // shipment is fine

    }

// Main function

    function processShipments(csv){
        const rows = parseCSV(csv);

        const processed = [];
        const exceptions = [];
        const errors = [];
        const seenIds = new Set();

        const today = new Date("2026-01-06");

        rows.forEach((row, index)=>{  // for each row and its position number

            const rowErrors = validateRow(row);

            if(seenIds.has(row.shipment_id)){
                rowErrors.push("Duplicate shipment_id");
            }

            if(rowErrors.length > 0){
                errors.push({
                    rowIndex: index + 1, // as at index 0 its the header
                    shipment_id: row.shipment_id,
                    errors: rowErrors

                }

                );

                return; // why do i need this - because it means that this row has an error so like skip it and save the error
            }

            const expected = Number(row.expected_qty); // why do i need to cast it as a number
            const received = Number(row.received_qty);

            const status = deriveStatus(expected, received);

            const record = {
                ...row, // what is this ... -> apparently the spead operator it makes a copy so like it takws the row object aqnd makes it into a copy inside the record
                expected_qty : expected,// i override because it was copied over as a string and i typecasted it into a number
                received_qty : received,
                status
            };

            processed.push(record);
            seenIds.add(row.shipment_id);

            const exceptionReason = isException(record, today);
            if(exceptionReason){
                exceptions.push({
                    shipment_id : record.shipment_id,
                    reason : exceptionReason
                });
            }

        });

        // you gotta drill this mamacita
        const summary = processed.reduce((acc, item) =>{
            acc[item.status] = (acc[item.status] || 0) + 1; // so beautiful the magic line eh
            return acc; // return the notebook 
        }, {});

        return {processed, summary, exceptions, errors};
    }
// Run and log result

        const result = processShipments(csvData);
        console.log(JSON.stringify(result, null, 2)); // json.stringify? and (result, null, 2)?
        // JSON.stringify like changes an object into a string
        