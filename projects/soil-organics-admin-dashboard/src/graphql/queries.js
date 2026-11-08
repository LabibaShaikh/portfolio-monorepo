import { gql } from '@apollo/client';

export const GET_USERS = gql`
  query GetUsers {
    users {
      email
      firstName
      lastName
      dateOfJoining
      blocked
    }
  }
`;

export const UPDATE_USER_BLOCK_STATUS = gql`
  mutation UpdateUserBlockStatus($email: String!, $blocked: Boolean!) {
    updateUserBlockStatus(email: $email, blocked: $blocked) {
      email
      blocked
    }
  }
`;

export const GET_ITEMS = gql`
  query GetItems {
    items {
      id
      prodName
      price
      qty
      onSale
      imgPath
    }
  }
`;

export const CREATE_ITEM = gql`
  mutation CreateItem($prodName: String!, $price: Float!, $qty: Int!, $onSale: Boolean!, $imgPath: String!) {
    createItem(prodName: $prodName, price: $price, qty: $qty, onSale: $onSale, imgPath: $imgPath) {
      id
      prodName
      price
      qty
      onSale
      imgPath
    }
  }
`;

export const UPDATE_ITEM = gql`
  mutation UpdateItem($id: ID!, $prodName: String, $price: Float, $qty: Int, $onSale: Boolean, $imgPath: String) {
    updateItem(id: $id, prodName: $prodName, price: $price, qty: $qty, onSale: $onSale, imgPath: $imgPath) {
      id
      prodName
      price
      qty
      onSale
      imgPath
    }
  }
`;

export const DELETE_ITEM = gql`
  mutation DeleteItem($id: ID!) {
    deleteItem(id: $id)
  }
`;
export const GET_REVIEWS = gql`
  query GetReviews {
    reviews {
      id
      userEmail
      itemId
      reviewText
      rating
      isDeleted
    }
  }
`;

export const ADD_REVIEW = gql`
  mutation AddReview($userEmail: String!, $itemId: Int!, $reviewText: String!, $rating: Int!) {
    addReview(userEmail: $userEmail, itemId: $itemId, reviewText: $reviewText, rating: $rating) {
      id
      userEmail
      itemId
      reviewText
      rating
      isDeleted
    }
  }
`;

export const UPDATE_REVIEW = gql`
  mutation UpdateReview($id: ID!, $reviewText: String!, $rating: Int!) {
    updateReview(id: $id, reviewText: $reviewText, rating: $rating) {
      id
      userEmail
      itemId
      reviewText
      rating
      isDeleted
    }
  }
`;

export const DELETE_REVIEW = gql`
  mutation DeleteReview($id: ID!) {
    deleteReview(id: $id)
  }
`;
export default { GET_USERS, UPDATE_USER_BLOCK_STATUS, GET_ITEMS, CREATE_ITEM, UPDATE_ITEM, DELETE_ITEM, GET_REVIEWS, DELETE_REVIEW};