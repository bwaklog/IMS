```text
    ______  ___
   /  _/  |/  /______  _______
   / // /|_/ / ___/ / / / ___/
 _/ // /  / (__  ) /_/ (__  )
/___/_/  /_/____/\__, /____/
                /____/
Inventory Management System written in C
```

> All the below can be found in commit `7a7f3e`

## Todo
- [ ] Querying directly from file
- [x] Storage of buckets
- [x] Modifying value of buckets
- [x] Deleting Buckets
- [x] Implementing a more dynamic Data structure
- [ ] Implement complete data reconstruction
  - [x] `OPADD` implementation
  - [x] `OPDEL` implementation
  - [ ] `OPSET` implementation
- [ ] Optimise reconstruction by not performing redundant operations
- [ ] Migrate to a client-server architecture 
  - Users can connect over to server using something as simple as `netcat`
  - All operations are similar to *Redis* operations such as `SET`, `GET`, `DEL`...
