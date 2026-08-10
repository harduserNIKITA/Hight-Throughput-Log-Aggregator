CREATE DATABASE IF NOT EXISTS logs_db;

USE logs_db;

CREATE TABLE IF NOT EXISTS app_logs(
    timestamp DateTime64(3, 'UTC') CODEC(DoubleDelta, ZSTD(1)),
    service_name LowCardinality(String) CODEC(ZSTD(1)),
    log_level LowCardinality(String) CODEC(ZSTD(1)),
    message Sting CODEC(ZSTD(3)),
    user_id UInt64 CODEC(T64, ZSTD(1))
)
ENGINE = MergeTree()
PRIMARY KEY (service_name, log_level)
ORDER BY (service_name, log_level, timestamp);
