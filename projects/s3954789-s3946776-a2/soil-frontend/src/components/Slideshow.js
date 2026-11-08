import React from "react";
import { Link } from "react-router-dom";
import "./Slideshow.css";

// Array holds images for the slideshow to display
const items = ["Corn.jpg", "MuesliBar.jpg", "Pasta.jpg", "Spinach.jpg", "Yoghurt.jpg"];

//Time delay
const delay = 5000;

//Slideshow Tutorial: https://tinloof.com/blog/how-to-build-an-auto-play-slideshow-with-react
function Slideshow () {


    // Hook to keep track of slide displays
    const [index, setIndex] = React.useState(0);
    const timeoutRef = React.useRef(null);


    // Clears timeOut each time the slide changes
    function resetTimeout() {
        if (timeoutRef.current) {
          clearTimeout(timeoutRef.current);
        }
    }


    // Hook to change slide every 5s
    React.useEffect(() => {
        resetTimeout();
        // setTimeout sets a time delay between each slide
        timeoutRef.current = setTimeout(
          () =>
            setIndex((prevIndex) =>
              prevIndex === items.length - 1 ? 0 : prevIndex + 1
            ),
          delay
        );
    
        return () => {
        resetTimeout();
        };
      }, [index]);


    //STYLING
    // Slideshow container
    const slideShowStyle = {
        margin: "0 auto",
        overflow: "hidden",
        width: "100%"
    };

    // Slideshow slider container
    const sliderStyle = {
        whiteSpace: "nowrap",
        transform: `translate3d(${-index * 100}%, 0, 0)`,
        transition: "ease 1000ms"
    };

    // Slides
    const slideStyle = {
        position: "relative",
        display: "inline-block",
        height: "500px",
        width: "100%",
        borderRadius: "40px"
    };

    // Images 
    const imageStyle = {
        position: "relative",
        width: "100%",
        height: "700px",
        fit: "cover"
    };

    //Buttons
    const slideshowDots = {
        textAlign: "center",
        position: "absolute",
        top: "90%",
        left: "45%"

    };

    //Inactive slide dots
    const inactiveDotStyle = {
        display: "inline-block",
        height: "20px",
        width: "20px",
        borderRadius: "50%",
        cursor: "pointer",
        margin: "15px 7px 0px",
        backgroundColor: "white"
    };

    //Active slide dots
    const activeDotStyle = {
        display: "inline-block",
        height: "20px",
        width: "20px",
        borderRadius: "50%",
        cursor: "pointer",
        margin: "15px 7px 0px",
        backgroundColor: "grey"
    };

    //Slideshow Caption + Shop Now Button
    const shopNowStyle = {
        position: "absolute",
        top: "40%",
        left: "20%",
        transform: "translate(-50%, -50%)",
    };


    return (
       //Slideshow container
      <div className="slideshow" style={slideShowStyle}>
        <div className="slideshowSlider" style={sliderStyle}>
            {items.map((imageUrl, index) => (
                <div className="slide" key={index} style={slideStyle}>
                    <img src={imageUrl} alt="Slide" style={imageStyle}/>
                    {/* Slide Show Caption + Shop Now Button */}
                    <div className="shopNow" style={shopNowStyle}>
                        <h3>Weekly Specials</h3>
                        <Link to="/Sales">
                            <button>SHOP NOW</button>
                        </Link> 
                    </div>
                </div>
            ))}
        </div>
        
        {/* Arrows to control slideshow */}
        <a className="prev"
                  onClick={() => {
                    setIndex(index-1 === 0 ? 4 : index-1);
                }}>❮
                </a>
        <a className="next"
                  onClick={() => {
                    setIndex(index+1 === items.length ? 0 : index+1);
                }}>❯
                </a>

        {/* Slideshow buttons */}
        <div className="slideshowDots" style={slideshowDots}>
            {items.map((_, idx) => (
            <div 
            key={idx} 
            className="slideshowDot" 
            style = {index === idx ? activeDotStyle : inactiveDotStyle}
            onClick={() => {
                setIndex(idx);
            }}
            >
            </div>
            ))}
            </div>
        </div>
    );
  }

  export default Slideshow;