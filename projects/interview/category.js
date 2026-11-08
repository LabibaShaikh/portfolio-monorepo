const express = require("express");
const app = express();

app.use(express.json());
let categories = [];

app.put( "/categories", (req, result) => {

    const {title, genre, sub_genre,  description} = req.body;
  
    // the tree organization structure:
    if (!genre){
        return res.status(404).json({ error: " Genre not found"});
    }

 else {

    categories.push(genre);
 }

 return res.status(201).json.strigify({genre});

});

app.get ("/categories/id", (req, res)  => {
     const id = (o => {o.id === req.params.id
         console.log(json(category));
     }
       
     );
});
app.listen (3000, () => {
 console.log(" Port running ");
});