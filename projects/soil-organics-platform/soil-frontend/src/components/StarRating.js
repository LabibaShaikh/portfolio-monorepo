import React, { useState } from 'react';
import Box from '@mui/material/Box';
import Rating from '@mui/material/Rating';

//This component allows user to select a Star rating (out of 5)
//to apply to a review
//Tutorial Used: https://codesandbox.io/p/sandbox/runtime-frost-xvxmhs?file=%2Fsrc%2FDemo.js%3A1%2C1-4%2C51

function StarRating( {handleRating} ) {
    //Hook to set star rating
    //Initial rating of 5 because our products deserve nothing less
    const [rating, setRating] = useState(5);

    return (
        //Box contains the star rating element
        <Box
          sx={{
            '& > legend': { mt: 2 },
          }}
        >
          <Rating
            name="simple-controlled"
            value={rating}
            //This function detects a change to rating
            //And sets this as the new value
            onChange={(event, newRating) => {
              setRating(newRating);
              //Pass back the new rating to parent
              handleRating(newRating);
            }}
          />
        </Box>
      );
};

export default StarRating;