import { render, screen } from "@testing-library/react";
import axios from "axios";
import ReviewModal from "../ReviewModal";
import { AuthProvider } from "../AuthContext";
import React from "react";
import { act } from "react-dom/test-utils";

//REVIEW UNIT TEST:
//Provides fake reviews, followed users and API fetch functions
//to the ReviewModal component.
//Checks whether the appropriate options to 
//'Edit', 'Delete', 'Follow' and 'Unfollow' are present

//Mock axios module
jest.mock("axios");

//Global data
const API_HOST = "http://localhost:4000";
let setIsOpen = jest.fn();
let setIsEditOpen = jest.fn();
let setReviewToEdit = jest.fn();

let reviews;
let followers;
let profiles;

//Mock of localStorage
const localStorageMock = (() => {
  let store = {};

  return {
    getItem: (key) => store[key],
    setItem: (key, value) => {
      store[key] = value.toString();
    },
    removeItem: (key) => {
      delete store[key];
    },
    clear: () => {
      store = {};
    },
  };
})();

Object.defineProperty(window, 'localStorage', {
  value: localStorageMock,
});

beforeAll(() => {
  });

// Set data for the component to use before tests,
beforeEach(() => {
  setIsOpen = jest.fn();
  setIsEditOpen = jest.fn();
  setReviewToEdit = jest.fn();

  //Set fake data to fetch
  reviews = [{id: 1, rating: 4, reviewText: "Review 1", datePublished: "05/15/2024", itemId: 1, userEmail: "user1@email.com"},
             {id: 2, rating: 1, reviewText: "Review 2", datePublished: "04/12/2024", itemId: 1, userEmail: "user2@email.com"},
             {id: 3, rating: 5, reviewText: "Review 3", datePublished: "01/21/2024", itemId: 1, userEmail: "user3@email.com"}];
  followers = [{id: 1, userEmail: "user1@email.com", userFollowsEmail: "user2@email.com"}];

  //Fake localStorage data
  profiles = [{id: 1, firstName: "User1_FirstName", lastName: "User1_LastName", email: "user1@email.com", password: "User1_Password", dateOfJoining: "2024-05-01"}];
  });


test('Review Modal updates ', async () => {
    //Set profiles in local storage
    window.localStorage.setItem("profiles", JSON.stringify(profiles));
    //Set logged in email in local storage
    window.localStorage.setItem("loggedInEmail", "user1@email.com");

    //Define mock implementations
    axios.get.mockImplementationOnce((url) => {
      console.log(`Axios called with the url: ${url}`);
      return Promise.resolve({ data: reviews });
    });

    axios.get.mockImplementationOnce((url) => {
      console.log(`Axios called with the url: ${url}`);
      return Promise.resolve({ data: followers });
    });

    //Use act() to enable automatic handling of state updates and async functions
    await act(async () => {
      render(<AuthProvider><ReviewModal itemId={1} setIsOpen={setIsOpen} setIsEditOpen={setIsEditOpen} setReviewToEdit={setReviewToEdit}></ReviewModal></AuthProvider>);
    })

    //Expecting 2 calls to the API:
    // 1. Fetch reviews
    // 2. Fetch followers
    expect(axios.get).toHaveBeenCalledWith(`${API_HOST}/api/reviews/select/${1}`);
    expect(axios.get).toHaveBeenCalledWith(`${API_HOST}/api/followers`, {"params": {"userEmail": "user1@email.com"}});

    //Based on user1 following user2 and user1 being logged in, we expect the following:
    //1 'Follow' button
    const followButtons = screen.getAllByText('Follow');
    expect(followButtons[0]).toBeInTheDocument();
    expect(followButtons).toHaveLength(1);

    //1 'Unfollow' button
    const unfollowButtons = screen.getAllByText('Unfollow');
    expect(unfollowButtons[0]).toBeInTheDocument();
    expect(unfollowButtons).toHaveLength(1);

    //1 'Edit' button
    const editButtons = screen.getAllByText('Edit');
    expect(editButtons[0]).toBeInTheDocument();
    expect(editButtons).toHaveLength(1);

    //1 'Delete' button
    const deleteButtons = screen.getAllByText('Delete');
    expect(deleteButtons[0]).toBeInTheDocument();
    expect(deleteButtons).toHaveLength(1);
});