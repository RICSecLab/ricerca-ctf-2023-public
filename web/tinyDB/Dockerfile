FROM node:18-buster-slim
COPY challenge /app
WORKDIR /app

RUN yarn && yarn build
RUN rm src/*.ts

EXPOSE 8888
CMD ["yarn", "start"]