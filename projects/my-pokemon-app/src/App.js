import logo from './logo.svg';
import './App.css';
import 'bootstrap/dist/css/bootstrap.min.css';
import { BrowserRouter as Router, Routes, Route } from "react-router-dom";
import Pokedex from './Pokedex';  
import PokemonList from './PokemonList';
import PokemonSearch from './PokemonSearch';
import PokemonCard from './PokemonCard';


/**
 * The main component of the application.
 *
 * @returns {JSX.Element} The rendered App component.
 */
function App() {
  return (
    <Router>
    <div className="App">
    
        <Routes>
          <Route path="/" element={<Pokedex />} />
          <Route path="/PokemonList" element={<PokemonList />} />
          <Route path="/PokemonSearch" element={<PokemonSearch />} />
          <Route path="/PokemonCard" element={<PokemonCard />} />
        </Routes>
   
     
    </div>
    </Router>
  );
}

export default App;
