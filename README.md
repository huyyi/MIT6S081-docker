# MIT6S081-docker
Docker environment of MIT6.S081 2021 labs

## Reports
- [syscall](https://github.com/huyyi/MIT6S081-docker/blob/master/reports/lab2-syscall.md)
- [Page tables](https://github.com/huyyi/MIT6S081-docker/blob/master/reports/lab3-pgtbl.md)
## How to use

### Setup docker container
1. Pull docker image
    ```shell 
    docker pull ghcr.io/huyyi/mit6s081-docker:latest
    ```
2. Run docker container with volume mapping
    ``` shell 
    docker run -itd --name=mit -v <xv6-directory>:/xv6 ghcr.io/huyyi/mit6s081-docker:latest
    ```
### Test your code
- In host: 
    ```shell 
    docker exec -it  mit bash
    ```

## Branches

- `master`: Docker environment files
- other: My solution to labs.

## Reference
[CalvinHaynes/MIT6.S081-2020-labs](https://github.com/CalvinHaynes/MIT6.S081-2020-labs)
