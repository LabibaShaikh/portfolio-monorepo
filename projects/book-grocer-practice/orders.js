
const express = require("express");
const app = express();

app.use(express.json());
const orders = [];

// create post

app.post("/orders", (req, res) =>{
        const {id, customer_emails, items} = req.body;

    if( !id || !customer_emails || !Array.isArray(items))  //last or 
    {return res.status(400).json({error: "Invalid order payload"});
}   // return res.status(400).json({ error : " Invalid "})
 const order = {
    id,
    customer_emails,
    items,
    status: "pending",
    createAt : new Date().toISOString()

 };

 orders.push(order);
 res.status(201).json(order);
});

// sends the response back to the client 201 is resource created successfullly and the newly created order is sent back to me
// get post

app.get("/orders", (req, res) =>{
    res.json(orders);
});

app.get("/orders/:id", (req, res) =>{
    const order = orders.find( o => o.id === req.params.id);

    if(!order){
        return res.status(404).json({ error: "Order not found"});
    }
    res.json(order);
})

// update/ put

app.put("/orders/:id", (req, res) =>{
    const { status } = req.body; // why did i put the status in {} its object destructuring  basically i just change the object into FIELD
    const order = orders.find( o => o.id === req.params.id);

    if(!order){
        return res.status(404).json({ error : "Error not found"});
    }

    // eRROR 404 IS NOT FOUND 

    if(!["pending", "fulfilled", "cancelled"].includes(status)){
        return res.status(400).json({ error : "Invalid status"});
    }

    order.status = status;
    res.json(order);
});

//order.status = status edits the original object inside orders.

app.delete("/orders/:id", (req, res) =>{
    const index = orders.findIndex(o => o.id === req.params.id);

    if( index === -1){
        return res.status(404).json({error: "Order not found"});
    }

    orders.splice(index, 1); // splice? “Starting at index, remove 1 item from the array.”
    res.status(204).send()
})
// 204 not found
// start server

app.listen(3000, () => {
    console.log("Server running on port 3000");
});

//