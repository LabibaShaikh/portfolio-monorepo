import { gql } from 'apollo-server-express';

const typeDefs = gql`
  type User {
    email: String!
    firstName: String!
    lastName: String
    dateOfJoining: String!
    blocked: Boolean!
  }
  type Item {
    id: ID!
    prodName: String!
    price: Float!
    qty: Int!
    onSale: Boolean!
    imgPath: String!
  }

  type Review {
    id: ID!
    userEmail: String!
    itemId: Int!
    reviewText: String!
    rating: Int!
    isDeleted: Boolean!
  }

  type Query {
    users: [User!]!
    items: [Item!]!
    reviews: [Review!]!
  }

  type Mutation {
    initializeBlockedField: String!
    updateUserBlockStatus(email: String!, blocked: Boolean!): User!
    createItem(prodName: String!, price: Float!, qty: Int!, onSale: Boolean!, imgPath: String!): Item
    updateItem(id: ID!, prodName: String, price: Float, qty: Int, onSale: Boolean, imgPath: String): Item
    deleteItem(id: ID!): Boolean
    deleteReview(id: ID!): Boolean!
  }
`;

export default typeDefs;
