import React from "react";
import "./DIYToolkit.css";

/**
 * Renders the DIY Toolkit component.
 * This component displays gardening tips and images for DIY gardening enthusiasts.
 *
 * @returns {JSX.Element} The rendered DIY Toolkit component.
 */
//Static page that displays useful tips
//For DIY Gardening
function DIYToolkit() {
    return (
        <div className="DIYToolkitWrapper">
            <h1>DIY Gardening Tips</h1>
            <div className="DIYGardenTipWrapper">
                <h2>Use raised-garden beds</h2>
                <p>Having a deep layer of soil will encourage healthy growth of your plants. 
                   A raised garden bed is especially good for growing:</p>
                <ul>
                    <li>Root vegetables such as carrots, beetroot, radishes and parsnips</li>
                    <li>Leafy greens like spinach, lettuce and kale</li>
                    <li>Tomatoes</li>
                    <li>Potatoes</li>
                    <li>Onions</li>
                </ul>
                <div className="tipImage">
                    <img src="gardenbed.jpg" alt="gardenbed.jpg" width="400px" height="400px"></img>
                </div>
            </div>
            <div className="DIYGardenTipWrapper">
                <h2>Grow directly in the ground</h2>
                <p>If you don’t plan on growing seedlings first, sow them directly in your garden bed. 
                   Before doing this, you should take care to remove large sticks, rocks, and weeds, and rake the soil to remove large clumps. 
                   This will raise your chances of a successful yield.</p>
                <div className="tipImage">
                    <img src="plantInGround.jpg" alt="plantInGround.jpg" width="400px" height="400px"></img>
                </div>
            </div>
            <div className="DIYGardenTipWrapper">
                <h2>Use a Greenhouse</h2>
                <p>Using an indoor greenhouse will allow light to reach your plants, while also creating 
                   the right temperature and air circulation for your plants to flourish! 
                   A greenhouse will also protect your veggies from factors like rain, snow, winds and insects.</p>
                <div className="tipImage">
                    <img src="greenhouse.jpg" alt="greenhouse.jpg" width="400px" height="400px"></img>
                </div>
            </div>
            <div className="DIYGardenTipWrapper">
                <h2>Use mulch</h2>
                <p>Mulch can boost your veggies’ growth by:</p>
                <ul>
                    <li>Preventing weed growth</li>
                    <li>Retaining moisture in your soil</li>
                    <li>Keeping soil warm during winter, and cool in the summer</li>
                    <li>Protects your soil from erosion due to wind</li>
                </ul>
                <div className="tipImage">
                    <img src="mulch.jpg" alt="mulch.jpg" width="400px" height="400px"></img>
                </div>
            </div>
            <div className="DIYGardenTipWrapper">
                <h2>Weed regularly</h2>
                <p>Remove weeds that might steal nutrients from your plants. Ideally, weed once a week.</p>
                <div className="tipImage">
                    <img src="weeds.jpg" alt="weeds.jpg" width="400px" height="400px"></img>
                </div>
            </div>
            <div className="DIYGardenTipWrapper">
                <h2>Use other supplements</h2>
                <p>Depending on the veggies you have, your supplier may provide or recommend extra fertilisers 
                   to supplement plant growth. These may include acid mixes, emulsions, mulch. 
                   If you have a pets like rabbits, guinea pigs, or chickens, you can also use their droppings as fertiliser!</p>
                <div className="tipImage">
                    <img src="fertiliser.jpg" alt="fertiliser.jpg" width="400px" height="400px"></img>
                </div>
            </div>
            <div className="DIYGardenTipWrapper">
                <h2>Use pesticide</h2>
                <p>If your plants are constantly overwhelmed with weeds and insects, consider using pesticides to get them under control.</p>
                <div className="tipImage">
                    <img src="pesticide.jpg" alt="pesticide.jpg" width="400px" height="400px"></img>
                </div>
            </div>
            <div className="DIYGardenTipWrapper">
                <h2>Grow seedlings</h2>
                <p>Some seeds are too fragile to grow straight in your garden bed! 
                   If you’re growing tomatoes, broccoli, cauliflower, cucumbers or peppers, start by growing them 
                   in small plant pots for a few weeks!</p>
                <div className="tipImage">
                    <img src="seedlings.jpg" alt="seedlings.jpg" width="400px" height="400px"></img>
                </div>
            </div>

        </div>
        
    );
}

export default DIYToolkit;