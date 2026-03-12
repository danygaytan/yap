# ADR 001: Websockets over other protocols

## Status
Accepted

## Context
Yap is a messaging app functioning on top of a terminal. Therefore, it needs a mechanism to send and receive
messages to multiple users on different sessions. Additionally, I want Yap to be decentralized, no
additional servers or nodes involved in sending and receiving messages, at least for 1 to 1 conversations.

## Decision
- Websockets
- Use websockets to implement 1 to 1 communication channels between users. Boost offers a reliable library to manage
websocket connection and operations.

## Alternatives considered
- HTTP
  * Using HTTP polling is not a good idea for a messaging experience, polling everytime a user wants to check for newer messages.
    This increases friction in the end user experience and is not as lightweight as websockets. 
- Custom protocol
  * Using a Custom protcol approach is still on the table. But for a start, I want to create a solid experience from where I can
    work on and implement better capabilities. Creating a custom protocol is a project itself, not worth it for the moment.

## Consequences
- A user yap app should work as client and server at the same time.
- Each time a user wants to chat to another one, a new client session should be created for further management.
- A single server instance (per user) can support multiple chats.


## Notes
- Authentication and keypair sharing need to be implemented to increase security. (Due to the lack of a central server).

